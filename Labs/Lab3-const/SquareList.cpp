///////////////////////////////////////////////////////////////
//  File:   SquareList.cpp
//  Course: CSCE-221 Data Structures & Algorithms
//  Author: 
//  Date:   9/6/2019
//  Usage:  You have to complete the implementation
///////////////////////////////////////////////////////////////

#include "SquareList.h"

SquareList::SquareList()
{
}

SquareList::~SquareList()
{
	for (std::list<InnerSquareList>::iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		iter->clean();
	}
}

void SquareList::consolidate()
{
	int n = 0;
	std::list<InnerSquareList>::iterator iter = inners.begin();
	while (iter != inners.end())
	{
		if (0 == iter->size())
		{
			//clean all empty inner lists
			iter = inners.erase(iter);
		}
		else
		{
			n += iter->size();
			iter++;
		}
	}

	bool foundShort = false;
	for (std::list<InnerSquareList>::iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		//split long inner lists into a half
		if (iter->size() > 2 * sqrt((double)n))
		{
			std::list<InnerSquareList>::iterator next = iter;
			next++;
			//insert before an iterator, STL function
			inners.insert(next, iter->split());
			iter++;
			continue;
		}

		if (iter->size() <= sqrt((double)n) / 2.)
		{
			if (false == foundShort)
			{
				//found first of two sequential short inner lists
				foundShort = true;
				continue;
			}
			else
			{
				//found two adjacent short lists
				std::list<InnerSquareList>::iterator current = iter;
				iter--;
				iter->merge(*current);
				inners.erase(current);
				foundShort = false;
				continue;
			}
		}
	}
}

void SquareList::addFirst(const int data)
{
	//insert an inner list before the first node
	if (inners.empty())
	{
		inners.push_back(InnerSquareList());
	}
	inners.front().addFirst(data);
	consolidate();
}

void SquareList::addLast(const int data)
{
	//insert an inner list before the first node
	if (inners.empty())
	{
		inners.push_back(InnerSquareList());
	}
	inners.back().addLast(data);
	consolidate();
}

void SquareList::add(int pos, const int data)
{
	//the first possible position is zero
	if (pos < 0)
	{
		return;
	}

	//first node in the SquareList
	if (0 == pos && inners.empty())
	{
		inners.push_back(InnerSquareList());
		inners.front().addFirst(data);
		return;
	}

	//general cases
	for (std::list<InnerSquareList>::iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		if (pos > (int)iter->size())
		{
			//move to next inner list
			pos -= iter->size();
		}
		else
		{
			//position in current inner list
			iter->add(pos, data);
			consolidate();
			return;
		}
	}
}

int SquareList::removeFirst()
{
	return remove(0);
}

int SquareList::remove(int pos)
{
	//index from zero
	if (pos < 0)
	{
		return INTNULL;
	}

	for (std::list<InnerSquareList>::iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		if (pos >= (int)iter->size())
		{
			//move to next inner list
			pos -= iter->size();
		}
		else
		{
			//position in current inner list
			int value = iter->remove(pos);
			consolidate();
			return value;
		}
	}
	return INTNULL;
}

int SquareList::get(int pos) const
{
	//index from zero
	if (pos < 0)
	{
		return INTNULL;
	}

	for (std::list<InnerSquareList>::const_iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		if (pos >= (int)iter->size())
		{
			//move to next inner list
			pos -= iter->size();
		}
		else
		{
			//position in current inner list
			return iter->get(pos);
		}
	}

	return INTNULL;
}

void SquareList::set(int pos, const int data)
{
	//index from zero
	if (pos < 0)
	{
		return;
	}

	for (std::list<InnerSquareList>::iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		if (pos >= (int)iter->size())
		{
			//move to next inner list
			pos -= iter->size();
		}
		else
		{
			//position in current inner list
			iter->set(pos, data);
			return;
		}
	}
}

int SquareList::size() const
{
	size_t sum = 0;
	//simply sum lengths of all inner lists
	for (std::list<InnerSquareList>::const_iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		sum += iter->size();
	}
	return sum;
}

int SquareList::indexOf(const int data) const
{
	size_t sum = 0;
	for (std::list<InnerSquareList>::const_iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		int id = iter->indexOf(data);
		if (-1 == id)
		{
			//move to next inner list
			sum += iter->size();
		}
		else
		{
			//position in current inner list
			return sum + id;
		}
	}
	//not found
	return -1;
}

void SquareList::dump() const
{
	std::cout << "*********************************************************" << std::endl;
	std::cout << "SquareList dump :" << std::endl;
	//information of the outer list
	std::cout << "Total size = " << size() << ", # of lists = " << inners.size() << std::endl;
	for (std::list<InnerSquareList>::const_iterator iter = inners.begin(); iter != inners.end(); iter++)
	{
		//display an inner list
		iter->dump();
	}
	std::cout << "*********************************************************" << std::endl;
}