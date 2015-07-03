#ifndef SPACE_HPP
#define SPACE_HPP

#include <map>
#include <vector>
namespace dcs{

static size_t chunkSize = 32;

template< typename T >
class SpaceChunk;

template<typename T>
class Space
{
public:
	Space (T defaultValue) :
    	m_defaultValue( defaultValue ){
		
	}
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
	
private:
	T m_defaultValue;
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
