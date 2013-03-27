
XCADShellps.dll: dlldata.obj XCADShell_p.obj XCADShell_i.obj
	link /dll /out:XCADShellps.dll /def:XCADShellps.def /entry:DllMain dlldata.obj XCADShell_p.obj XCADShell_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0500 /DREGISTER_PROXY_DLL \
		$<
# _WIN32_WINNT=0x0500 is for Win2000, change it to 0x0400 for NT4 or Win95 with DCOM

clean:
	@del XCADShellps.dll
	@del XCADShellps.lib
	@del XCADShellps.exp
	@del dlldata.obj
	@del XCADShell_p.obj
	@del XCADShell_i.obj
