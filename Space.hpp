#ifndef SPACE_HPP
#define SPACE_HPP

#include <map>
#include <vector>
#include <numeric>
namespace dcs{

static size_t chunkSize = 32;

template< typename T >
class SpaceChunk;

template<typename T>
class Space
{
public:
	//virtual ~Space ();

	T& get(int i, int j){
		int chunkI = i/chunkSize;
		int chunkJ = j/chunkSize;
		return m_map[ std::pair<int,int>( chunkI, chunkJ ) ].
    		m_grid[i%chunkSize][j%chunkSize];
	}

	void set(int i, int j, const T& v){
		int chunkI = i/chunkSize;
		int chunkJ = j/chunkSize;
		m_map[ std::pair<int,int>( chunkI, chunkJ ) ].
			m_grid[i%chunkSize][j%chunkSize] = v;
	}

	void bounds(int &leftInclusive, int &rightExclusive,
				int &bottomInclusive, int &topExclusive ){
		leftInclusive = std::numeric_limits<int>::max();
		rightExclusive = std::numeric_limits<int>::min();
		bottomInclusive = std::numeric_limits<int>::max();
		topExclusive = std::numeric_limits<int>::min();
		for (auto &i : m_map ) {
			if( i.first.first < leftInclusive )
				leftInclusive = i.first.first;
			if( i.first.first > rightExclusive ) 
				rightExclusive = i.first.first + 1;
			if( i.first.second < bottomInclusive )
				bottomInclusive = i.first.second;
			if( i.first.second > topExclusive) 
				topExclusive = i.first.second + 1;

		}

	}
	
private:
	std::map< std::pair<int,int>, SpaceChunk<T>> m_map;
};


template< typename T >
class SpaceChunk{

	friend class Space<T>;
	std::vector< std::vector< T > > m_grid;

public:
	SpaceChunk(){
    	for (int i = 0; i < chunkSize; ++i)
    	{
			m_grid.push_back( std::vector<T>() );
    		for (int j = 0; j < chunkSize; ++j)
    		{
				m_grid[i].push_back( T() );
    		}
    	}
	}
};
}// namespace
#endif /* end of include guard: SPACE_HPP */
