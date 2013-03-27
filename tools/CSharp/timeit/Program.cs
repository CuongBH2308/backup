using System;
using System.IO;
using System.ComponentModel;
using System.Diagnostics;
using System.Collections.Generic;
using System.Text.RegularExpressions;

// This program handles different executables:
// 1. native executable: .exe
// 2. scripts: .bat, .cmd, .pl
// 3. dos commands: dir, del, echo... get it from the "cmd /c help"


namespace timeit
{
    public class Program
    {
  
        static int Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("Usage: timeit <program> [args...]");
                return -1;
            }

            string[] finalArgs = TwistArgs(args);


            Stopwatch timer = new Stopwatch();
            timer.Start();

            // Run the actual program
            int exitCode = 0;
            try
            {
                exitCode = RunProgram(finalArgs);
            }
            catch (Win32Exception)
            {
                Console.WriteLine("\"" + args[0] + "\"" + " is not a valid program!");
                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return -1;
            }

            timer.Stop();

            OutputTime(timer);

            return exitCode;
        }

        static int RunProgram(string[] args)
        {
            string exe = args[0];
            string argLine = null;
            if (args.Length > 1)
            {
                argLine = args[1];
                for (int i = 2; i < args.Length; ++i)
                {
                    argLine = argLine + " " + args[i];
                }
            }

            Console.WriteLine("Timing: " + exe + " " + argLine + "...\n");

            var process = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = exe,
                    Arguments = argLine,
                    UseShellExecute = false,
                    RedirectStandardError = true,
                    RedirectStandardInput = true,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }
            };

            process.OutputDataReceived += OutputDataReceived;
            process.ErrorDataReceived += ErrorDataReceived;

            process.Start();
            process.BeginOutputReadLine();
            process.BeginErrorReadLine();

            process.WaitForExit();

            return process.ExitCode;
        }

        static void OutputDataReceived(object o, DataReceivedEventArgs args)
        {
            Console.WriteLine(args.Data);
        }

        static void ErrorDataReceived(object o, DataReceivedEventArgs args)
        {
            if (!string.IsNullOrEmpty(args.Data))
                Console.WriteLine("ERROR: " + args.Data);
        }

        static void OutputTime(Stopwatch timer)
        {
            TimeSpan ts = timer.Elapsed;

            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
                ts.Hours, ts.Minutes, ts.Seconds,
                ts.Milliseconds / 10);
            Console.WriteLine("Elapsed Time: " + elapsedTime);
        }

        // Resolve the full path of a file name
        // fileName: of absolute path or relative path; with ext or without ext
        public static string ResolvePath(string fileName)
        {
            // 0. absolute path
            string[] stdExts = { ".bat", ".cmd", ".pl", ".exe" };
            if (Path.IsPathRooted(fileName))
            {
                if (File.Exists(fileName))
                {
                    return fileName;
                }
                else
                {
                    foreach (string eachExt in stdExts)
                    {
                        string fullPath = fileName + eachExt;
                        if (File.Exists(fullPath))
                        {
                            return fullPath;
                        }
                    }
                }

                return "";
            }

            // 1. candidate extensions
            string fileNameNoExt = Path.GetFileNameWithoutExtension(fileName);
            string ext = Path.GetExtension(fileName);
            string[] candidateExts;
            if (string.IsNullOrEmpty(ext))
            {
                candidateExts = stdExts;
            }
            else
            {
                string[] exts = { ext };
                candidateExts = exts;
            }

            // 2. candidate path:
            //      http://msdn.microsoft.com/en-us/library/windows/desktop/ms682586(v=vs.85).aspx#search_order_for_desktop_applications
            List<string> candidatePaths = new List<string>();

            // application dir
            string fileApp = Process.GetCurrentProcess().MainModule.FileName;
            candidatePaths.Add(Path.GetDirectoryName(fileApp));

            // current dir
            candidatePaths.Add(Directory.GetCurrentDirectory());

            // system dir
            candidatePaths.Add(Environment.SystemDirectory);

            // windows dir
            string winDir = Environment.GetEnvironmentVariable("windir");
            candidatePaths.Add(winDir);

            // PATH
            string[] paths = Environment.GetEnvironmentVariable("PATH").Split(';');
            foreach (string path in paths)
            {
                // strip the trailing '\'
                candidatePaths.Add(Path.GetDirectoryName(path));
            }

            // 3. resolve
            foreach (string eachPath in candidatePaths)
            {
                foreach (string eachExt in candidateExts)
                {
                    string fullPath = eachPath + "\\" + fileNameNoExt + eachExt;
                    if (File.Exists(fullPath))
                        return fullPath;
                }
            }

            return "";
        }

        static HashSet<string> GetDosCmds()
        {
            var process = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "cmd",
                    Arguments = "/c help",
                    UseShellExecute = false,
                    RedirectStandardError = false,
                    RedirectStandardInput = false,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }
            };

            process.Start();

            // Don't call process.WaitForExit() to avoid a deadlock condition by calling p.StandardOutput.ReadToEnd before p.WaitForExit. 
            // A deadlock condition can result if the parent process calls p.WaitForExit before p.StandardOutput.ReadToEnd 
            // and the child process writes enough text to fill the redirected stream. The parent process would wait indefinitely
            // for the child process to exit. The child process would wait indefinitely for the parent to read from the full StandardOutput stream.
            string helpOutput = process.StandardOutput.ReadToEnd();

            HashSet<string> dosCmds = new HashSet<string>();
            string [] helpOutputs = helpOutput.Split(new string[] { "\r\n" }, StringSplitOptions.None);
            foreach (string eachHelp in helpOutputs)
            {
                Match mt= Regex.Match(eachHelp, @"^\w+");
                if(mt.Success)
                    dosCmds.Add(mt.Value);
            }

            return dosCmds;
        }

        // Twist arguments for non .exe executables (scripts) or Dos commands
        static string[] TwistArgs(string[] args)
        {
            string executable = args[0];
            string[] addedArgs = null;

            HashSet<string> dosCmds = GetDosCmds();

            if (dosCmds.Contains(executable.ToUpper()))
            {
                // Dos commands
                addedArgs = new string[] { "cmd", "/c" };
            }
            else
            {
                
                Dictionary<string, string[]> extExeMap = new Dictionary<string, string[]>
                {
                    {".bat", new string [] {"cmd", "/c"}},
                    {".cmd", new string [] {"cmd", "/c"}},
                    {".pl", new string [] {"perl"}}
                };

                string fullPath = ResolvePath(executable);

                if (!string.IsNullOrEmpty(fullPath))
                {
                    string ext = Path.GetExtension(fullPath);
                    if (extExeMap.ContainsKey(ext))
                    {
                        // Scripts
                        addedArgs = extExeMap[ext];
                        executable = fullPath;
                    }
                }
            }

            string[] finalArgs;
            if (addedArgs != null)
            {
                int finalSize = args.Length;
                finalSize += addedArgs.Length;

                string[] tmpFinalArgs = new string[finalSize];
                int index = 0;
                for (int i = 0; i < addedArgs.Length; ++i)
                {
                    tmpFinalArgs[index++] = addedArgs[i];
                }

                // replace the executable with full path if it is a script
                tmpFinalArgs[index++] = executable;

                for (int i = 1; i < args.Length; ++i)
                {
                    tmpFinalArgs[index++] = args[i];
                }

                finalArgs = tmpFinalArgs;

            }
            else
                finalArgs = args;

            return finalArgs;
        }
    }
}