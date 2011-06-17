#!/usr/bin/perl -w

#   Copyright 2011 PureSol Technologies
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

open SOURCE, ">oclStdKernels.c";
print SOURCE "#include \"oclStdKernels.h\"\n";

open HEADER, ">oclStdKernels.h";
print HEADER "#ifndef OCL_KERNELS_H\n";
print HEADER "#define OCL_KERNELS_H\n";

foreach $file (`find -type f -name '*.ocl'`) {
	chomp $file;
	$name = $file;
	$name =~ s/^.*\/([^\/]*)\.ocl$/ocl$1/;

	print HEADER "\n";
	print HEADER
"/*****************************************************************************\n";
	print HEADER " * Auto-generated string constant from OpenCL source file\n";
	print HEADER " * '$file'.\n";
	print HEADER
" * This constant is used to put the OpenCL source within the binary and to\n";
	print HEADER " * hand it to the OpenCL compiler of the present devices.\n";
	print HEADER
" ****************************************************************************/\n";
	print HEADER "const char *" . $name . ";\n";

	print SOURCE "\n";
	print SOURCE "const char *" . $name . " =";
	foreach (`cat $file`)
	{
		chomp;
		if (m/^#/) {
			next;
		}
		s/\\/\\\\"/g;
		s/\"/\\"/g;
		print SOURCE "\n";
		print SOURCE "    \"";
		print SOURCE;
		print SOURCE "\\n\"";
	}
	print SOURCE ";\n";
}

print HEADER "\n";
print HEADER "#endif\n";
close HEADER;

close SOURCE;
