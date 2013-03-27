
AddInSampleps.dll: dlldata.obj AddInSample_p.obj AddInSample_i.obj
	link /dll /out:AddInSampleps.dll /def:AddInSampleps.def /entry:DllMain dlldata.obj AddInSample_p.obj AddInSample_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0500 /DREGISTER_PROXY_DLL \
		$<
# _WIN32_WINNT=0x0500 is for Win2000, change it to 0x0400 for NT4 or Win95 with DCOM

clean:
	@del AddInSampleps.dll
	@del AddInSampleps.lib
	@del AddInSampleps.exp
	@del dlldata.obj
	@del AddInSample_p.obj
	@del AddInSample_i.obj
