extern "C" {
	#include "plapi.h"
	#include "gserrors.h"
}
#include <iostream>
#include "pcl2pdf.h"

using namespace std;
//pcl ±êÊ¶·û
#pragma comment(lib, "gpcl6dll32.lib")
int main(int argc, char* argv[])
{
	return pcl2pdf(argv[1],argv[2]);
}