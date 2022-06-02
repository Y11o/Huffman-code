#include "pch.h"
#include "CppUnitTest.h"
#include "..\HuffmanTree\Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HuffmanTreeTest
{
	TEST_CLASS(HuffmanTreeTest)
	{
	public:
		
		TEST_METHOD(HuffmanCode)
		{
			string test = "It's testing string.";
			buildHuffmanTree(test);
			string encodedString = "0010 01 11110 110 100 01 0011 110 01 1011 1110 000 100 110 01 1010 1011 1110 000 11111 ";
			Assert::AreEqual(encodedString, forTest.encodedText);
			Assert::AreEqual(test, forTest.decodedText);

		}
	};
}
