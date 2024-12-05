//import <vector>;
#include <vector>
//import <iostream>;
#include <iostream>
//import <algorithm>;
#include <algorithm>
//import <format>;
#include <format>
//import <random>;
#include <random>
//import <iterator>;
#include <iterator>

#include <chrono>
//import <chrono>;
#include <execution>
#include <cmath>

int main(int argc, char *argv[])
{
	constexpr int Size = 10'000'000;

	// Integers
	std::vector<int> data(Size);
	std::random_device rdev;
	std::default_random_engine reng(rdev());
	std::uniform_int_distribution rdistr(0, Size);

	std::generate(data.begin(), data.end(), [&]() { return rdistr(reng); });

	std::cout << "Fitst ten random values of data:" << std::endl;
	std::cout << "\t";
	std::copy_n(data.begin(), 10, std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "..." << std::endl;

	// Sequential
	std::vector<int> dataSeq(data);
	auto startSeq = std::chrono::steady_clock::now();
	std::sort(dataSeq.begin(), dataSeq.end());
	auto finishSeq = std::chrono::steady_clock::now();
	auto durSeq = std::chrono::duration_cast<std::chrono::milliseconds>(finishSeq - startSeq);

	std::cout << std::format("Sorting sequentially {} records takes {} ms.", dataSeq.size(), durSeq.count()) << std::endl;
	
	// Parallel
	std::vector<int> dataPar(data);
	auto startPar = std::chrono::steady_clock::now();
	std::sort(std::execution::par, dataPar.begin(), dataPar.end());
	auto finishPar = std::chrono::steady_clock::now();
	auto durPar = std::chrono::duration_cast<std::chrono::milliseconds>(finishPar - startPar);

	std::cout << std::format("Sorting parallel {} records takes {} ms.", dataPar.size(), durPar.count()) << std::endl;

	// Transform Sequential
	std::vector<int> dataSqrtSeq(data);
	auto startSqrtSeq = std::chrono::steady_clock::now();
	std::transform(std::execution::seq, dataSqrtSeq.begin(), dataSqrtSeq.end(), dataSqrtSeq.begin(), [](int x) { return std::sqrt(x); });
	auto finishSqrtSeq = std::chrono::steady_clock::now();
	auto durSqrtSeq = std::chrono::duration_cast<std::chrono::milliseconds>(finishSqrtSeq - startSqrtSeq);
	std::cout << std::format("Sqrt sequential {} records takes {} ms.", dataSqrtSeq.size(), durSqrtSeq.count()) << std::endl;

	// Transform Parallel
	std::vector<int> dataSqrtPar(data);
	auto startSqrtPar = std::chrono::steady_clock::now();
	std::transform(std::execution::par, dataSqrtPar.begin(), dataSqrtPar.end(), dataSqrtPar.begin(), [](int x) { return std::sqrt(x); });
	auto finishSqrtPar = std::chrono::steady_clock::now();
	auto durSqrtPar = std::chrono::duration_cast<std::chrono::milliseconds>(finishSqrtPar - startSqrtPar);
	std::cout << std::format("Sqrt parallel {} records takes {} ms.", dataSqrtPar.size(), durSqrtPar.count()) << std::endl;

	// Transform Parallel Unsequenced
	std::vector<int> dataSqrtParUnseq(data);
	auto startSqrtParUnseq = std::chrono::steady_clock::now();
	std::transform(std::execution::par_unseq, dataSqrtParUnseq.begin(), dataSqrtParUnseq.end(), dataSqrtParUnseq.begin(), [](int x) { return std::sqrt(x); });
	auto finishSqrtParUnseq = std::chrono::steady_clock::now();
	auto durSqrtParUnseq = std::chrono::duration_cast<std::chrono::milliseconds>(finishSqrtParUnseq - startSqrtParUnseq);
	std::cout << std::format("Sqrt parallel unsequenced {} records takes {} ms.", dataSqrtParUnseq.size(), durSqrtParUnseq.count()) << std::endl;

	// Floatig point (double)
	std::vector<double> dblData(Size);
	std::uniform_real_distribution rdbldistr(0.0, 1000.0);

	std::generate(dblData.begin(), dblData.end(), [&]() { return rdbldistr(reng); });

	std::cout << "Fitst ten random values of double data:" << std::endl;
	std::cout << "\t";
	std::copy_n(dblData.begin(), 10, std::ostream_iterator<double>(std::cout, ", "));
	std::cout << "..." << std::endl;

	// Transform Sequential
	std::vector<double> dblDataSqrtSeq(dblData);
	auto startDblSqrtSeq = std::chrono::steady_clock::now();
	std::transform(std::execution::seq, dblDataSqrtSeq.begin(), dblDataSqrtSeq.end(), dblDataSqrtSeq.begin(), [](double x) { return std::sqrt(x); });
	auto finishDblSqrtSeq = std::chrono::steady_clock::now();
	auto durDblSqrtSeq = std::chrono::duration_cast<std::chrono::milliseconds>(finishDblSqrtSeq - startDblSqrtSeq);
	std::cout << std::format("Sqrt double sequential {} records takes {} ms.", dblDataSqrtSeq.size(), durDblSqrtSeq.count()) << std::endl;

	// Transform Parallel
	std::vector<double> dblDataSqrtPar(dblData);
	auto startDblSqrtPar = std::chrono::steady_clock::now();
	std::transform(std::execution::par, dblDataSqrtPar.begin(), dblDataSqrtPar.end(), dblDataSqrtPar.begin(), [](double x) { return std::sqrt(x); });
	auto finishDblSqrtPar = std::chrono::steady_clock::now();
	auto durDblSqrtPar = std::chrono::duration_cast<std::chrono::milliseconds>(finishDblSqrtPar - startDblSqrtPar);
	std::cout << std::format("Sqrt double parallel {} records takes {} ms.", dblDataSqrtPar.size(), durDblSqrtPar.count()) << std::endl;

	// Transform Parallel Unsequenced
	std::vector<double> dblDataSqrtParUnseq(dblData);
	auto startDblSqrtParUnseq = std::chrono::steady_clock::now();
	std::transform(std::execution::par_unseq, dblDataSqrtParUnseq.begin(), dblDataSqrtParUnseq.end(), dblDataSqrtParUnseq.begin(), [](double x) { return std::sqrt(x); });
	auto finishDblSqrtParUnseq = std::chrono::steady_clock::now();
	auto durDblSqrtParUnseq = std::chrono::duration_cast<std::chrono::milliseconds>(finishDblSqrtParUnseq - startDblSqrtParUnseq);
	std::cout << std::format("Sqrt double  parallel unsequenced {} records takes {} ms.", dblDataSqrtParUnseq.size(), durDblSqrtParUnseq.count()) << std::endl;

	return EXIT_SUCCESS;

}
