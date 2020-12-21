#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/lab3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	private:
		List* vec = new List();
		Heap* heap = new Heap();
	public:
		TEST_METHOD_INITIALIZE(init) {
			vec->pushBack(1);
			vec->pushBack(2);
			vec->pushBack(3);
			heap->insert(1);
			heap->insert(2);
			heap->insert(4);
			heap->insert(3);
			heap->insert(0);
			heap->insert(-1);
		}
		TEST_METHOD(test_getEnd)
		{
			Assert::AreEqual(vec->getEnd()->n, 3);
		}
		TEST_METHOD(test_pushBack)
		{
			vec->pushBack(4);
			Assert::AreEqual(vec->getEnd()->n, 4);
		}
		TEST_METHOD(test_popBack)
		{
			vec->popBack();
			Assert::AreEqual(vec->getEnd()->n, 2);
			vec->popBack();
			Assert::AreEqual(vec->getEnd()->n, 1);
			vec->popBack();
			Assert::AreEqual(vec->size, 0);
		}
		TEST_METHOD(test_heap_methods)
		{
			Assert::IsTrue(heap->contains(1));
			Assert::IsTrue(heap->contains(2));
			Assert::IsTrue(heap->contains(3));
			Assert::IsTrue(heap->contains(4));
			Assert::IsTrue(heap->contains(0));
			Assert::IsTrue(heap->contains(-1));
			Assert::IsFalse(heap->contains(-5));
			heap->insert(5);
			heap->insert(6);
			Assert::IsTrue(heap->contains(5));
			Assert::IsTrue(heap->contains(6));
			heap->remove(6);
			heap->remove(5);
			heap->remove(4);
			heap->remove(3);
			heap->remove(2);
			heap->remove(1);
			heap->remove(0);
			Assert::IsFalse(heap->contains(6));
			Assert::IsFalse(heap->contains(5));
			Assert::IsFalse(heap->contains(4));
			Assert::IsFalse(heap->contains(3));
			Assert::IsFalse(heap->contains(2));
			Assert::IsFalse(heap->contains(1));
			Assert::IsFalse(heap->contains(0));
			Assert::IsTrue(heap->contains(-1));
		}
		TEST_METHOD(test_DFT)
		{
			auto iter = heap->create_dft_iterator();
			Assert::AreEqual(iter.val(), 4);
			Assert::AreEqual((++iter).val(), 3);
			Assert::AreEqual((++iter).val(), 1);
			Assert::AreEqual((++iter).val(), 0);
			Assert::AreEqual((++iter).val(), 2);
			Assert::AreEqual((++iter).val(), -1);
			Assert::AreEqual((++iter).val(), -1);
			Assert::AreEqual((--iter).val(), 2);
			Assert::AreEqual((--iter).val(), 0);
			Assert::AreEqual((--iter).val(), 1);
			Assert::AreEqual((--iter).val(), 3);
			Assert::AreEqual((--iter).val(), 4);
			Assert::AreEqual((iter+2).val(), 1);
		}
		TEST_METHOD(test_BFT)
		{
			auto iter = heap->create_bft_iterator();
			Assert::AreEqual(iter.val(), 4);
			Assert::AreEqual((++iter).val(), 3);
			Assert::AreEqual((++iter).val(), 2);
			Assert::AreEqual((++iter).val(), 1);
			Assert::AreEqual((++iter).val(), 0);
			Assert::AreEqual((++iter).val(), -1);
			Assert::AreEqual((++iter).val(), -1);
			Assert::AreEqual((--iter).val(), 0);
			Assert::AreEqual((--iter).val(), 1);
			Assert::AreEqual((--iter).val(), 2);
			Assert::AreEqual((--iter).val(), 3);
			Assert::AreEqual((--iter).val(), 4);
			Assert::AreEqual((iter + 2).val(), 2);

		}
	};
}
