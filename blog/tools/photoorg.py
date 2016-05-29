import argparse
import os
import time

ignore_count = 0
error_count = 0
moved_count = 0
def get_target_dir(file):
    subdir = time.strftime('%Y-%m', time.gmtime(os.path.getmtime(file))) # you should use getmtime, not getctime, as once copied, the create time will be updated
    return subdir
    
def move_to(src, target_dir):
    print "Move %s to %s" % (src, target_dir)
    if not os.path.isdir(target_dir):
        os.mkdir(target_dir)
    dst = os.path.join(target_dir, os.path.basename(src))
    if os.path.isfile(dst):
        global ignore_count
        ignore_count = ignore_count + 1
        print dst + " already exists."
    else:
        global moved_count
        moved_count = moved_count + 1
        os.rename(src, dst) # shutil.move is also an option

    
if __name__ == '__main__':
    # process arguments
    parser = argparse.ArgumentParser(description = "Orgnaize photos from source directory into target directory, as YYYY-MM sub directories")
    parser.add_argument('source',help = "the source directory")
    parser.add_argument('target', help = "the target directory")
    parser.add_argument('-r','--recursive', action='store_true', help = "Handle files from source recursively")
    args = parser.parse_args()
    
    # get all files to move
    all_files = []
    for root, dirs, files in os.walk(args.source):
        all_files = all_files + [os.path.join(root, file) for file in files]
        if not args.recursive:
            break
        
    for file in all_files:
        try:
            target_dir = get_target_dir(file)
            move_to(file, os.path.join(args.target, target_dir))
        except Exception as e:
            print "Error: Failed to process file " + file
            error_count = error_count + 1

    print "Summary:"
    print "Files moved: %s" % (moved_count)
    print "Files ignored (already in target): %s" % (ignore_count)
    print "Files errored out): %s" % (error_count)