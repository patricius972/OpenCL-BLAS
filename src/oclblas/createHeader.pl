#!/usr/bin/perl -w

open SOURCE, ">oclStdKernels.c";
print SOURCE "#include \"oclStdKernels.h\"\n";

open HEADER, ">oclStdKernels.h";
print HEADER "#ifndef OCL_KERNELS_H\n";
print HEADER "#define OCL_KERNELS_H\n";

foreach $file (`find -type f -name '*.ocl'`)
{
	chomp $file;
	$name = $file;
	$name =~ s/^.*\/([^\/]*)\.ocl$/ocl$1/;

	print HEADER "\n";
	print HEADER "/*****************************************************************************\n";
	print HEADER " * Auto-generated string constant from OpenCL source file\n";
	print HEADER " * '$file'.\n";
	print HEADER " * This constant is used to put the OpenCL source within the binary and to\n";
	print HEADER " * hand it to the OpenCL compiler of the present devices.\n";
	print HEADER " ****************************************************************************/\n";
	print HEADER "const char *".$name.";\n";

	print SOURCE "\n";
	print SOURCE "const char *".$name." =";
	foreach (`cat $file`) 
	{
		chomp;
		if (m/^#/) 
		{
			next;
		}
		s/\"/\\"/;
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
