#include "risc0/zkvm/sdk/cpp/host/receipt.h"
#include <iostream>
#include <cxxopts.hpp>

int main (int argc,char** argv)
{
	cxxopts::Options options("Receipt verification", "Reciept verification tool");

	options.add_options()
		("m,method", "Method file", cxxopts::value<std::string>())
		("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
	;
	
	auto result = options.parse(argc, argv);

	std::string method = result["method"].as<std::string>();
	bool verbose = result["verbose"].as<bool>();

	if (verbose)
		std::cout<<"Using a method file:"<<method<<std::endl;

	risc0::Receipt receipt;
	receipt.verify(method);
}
