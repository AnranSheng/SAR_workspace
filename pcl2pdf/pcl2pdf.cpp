#include "pcl2pdf.h"
extern "C" {
#include "plapi.h"
#include "gserrors.h"
}
#include <string.h>
#include <stdio.h>
//pcl ±êÊ¶·û
#define PJL_UEL "\033%-12345X"
#pragma comment(lib, "gpcl6dll32.lib")

int pcl2pdf(const char* pclpath, const char* pdfsavepath) {
	printf("pclpath:%s,pdfsavepath:%s\n", pclpath, pdfsavepath);
	if (pclpath == nullptr || pdfsavepath == nullptr||strlen(pclpath) == 0||strlen(pdfsavepath) == 0)
	{
		return -1;
	}
	int dummy, codel;
	size_t uel_len = strlen(PJL_UEL);
	const char* argv[5];//[96]= { "", "-dNOPAUSE", "-sDEVICE=pdfwrite", "-sOutputFile=test.pdf", "test.pcl" };
	const char* outputformat = "-sOutputFile=%s";
	char buffer[128] = { 0 };
	snprintf(buffer, sizeof(buffer), outputformat, pdfsavepath);
	printf("format:%s", buffer);
	argv[0] = "pcl2pdf.exe";
	argv[1] = "-dNOPAUSE";
	argv[2] = "-sDEVICE=pdfwrite";
	argv[3] = buffer;
	argv[04] = pclpath;
	void* minst = nullptr;
	int code = gsapi_new_instance(&minst, (void*)0);
	if (code < 0)
		return -1;
	code = gsapi_init_with_args(minst, 5, (char**)argv);
	if (code >= 0)
		code = gsapi_run_string_begin(minst, 0, &dummy);
	if (code >= 0)
		code = gsapi_run_string_continue(minst, PJL_UEL, uel_len, 0, &dummy);
	if (code >= 0)
		code = gsapi_run_string_end(minst, 0, &dummy);
	if (code == gs_error_InterpreterExit)
		code = 0;
	codel = gsapi_exit(minst);
	if ((code == 0) || (code == gs_error_Quit))
		code = codel;
	gsapi_delete_instance(minst);
	if ((code == 0) || (code == gs_error_Quit))
		return 0;
	return code;
}