#ifndef DIRECTED_GRAPH_TEST_H
#define DIRECTED_GRAPH_TEST_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <assert.h>

#include "../DirectedGraph.h"
#include "NFATest.h"

namespace anyun_regex
{
	using std::cout;
	using std::setw;
	using std::endl;
	using std::ifstream;
	using std::ofstream;
	using std::ostream;
	using std::find;
	using std::stringstream;
	using std::vector;
	using std::string;
#ifdef _DEBUG


	int test_directedgraph();
	class DirectedGraphTest
	{
	public:
		DirectedGraphTest();
		void test();
	private:
		DirectedGraph diagraph;
		size_t test_count;
		size_t pass_count;
		void test_compile_normal();
		void test_compile_error();
		void test_pre_process_normal();
		void test_pre_process_error();
	};
#endif // _DEBUG

}


#endif // !DIRECTED_GRAPH_TEST_H
