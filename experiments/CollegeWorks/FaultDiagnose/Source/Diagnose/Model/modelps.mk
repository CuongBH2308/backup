
modelps.dll: dlldata.obj model_p.obj model_i.obj
	link /dll /out:modelps.dll /def:modelps.def /entry:DllMain dlldata.obj model_p.obj model_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del modelps.dll
	@del modelps.lib
	@del modelps.exp
	@del dlldata.obj
	@del model_p.obj
	@del model_i.obj
