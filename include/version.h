# ifndef   __WIRES_INCLUDE_VERSION_H_
#  define  __WIRES_INCLUDE_VERSION_H_ 1

namespace Wires
{
	class SemVer;
	
	SemVer GetVersion();
};

class Wires::SemVer
{
public :
	unsigned m_major, m_minor, m_patch;
};

# endif /* __WIRES_INCLUDE_VERSION_H_ */
