#ifndef __g2d_enum_h
#define __g2d_enum_h

namespace osl {
namespace g2d {

enum OffsetExtremeType
{
	betNone,
	betRound
};

/*! Item's tag of close offset */
enum OffsetTag
{
	NotSet,
	Direct,
	Reverse,
	StartExtreme,
	EndExtreme,
	Link
};

}
}

#endif