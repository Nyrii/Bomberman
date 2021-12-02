//
// CMeshCombiner.hh for CMeshCombiner in /home/wilmot_g/Rendu/cpp_indie_studio
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Sun Jun  5 17:12:23 2016 guillaume wilmot
// Last update Sun Jun  5 17:13:10 2016 Nyrandone Noboud-Inpeng
//

#ifndef CMESHCOMBINER_HH_
# define CMESHCOMBINER_HH_

# include <irrlicht.h>
# include <stdlib.h>

class CRectPacker {
public:
  struct SPacked {
    irr::core::rect<irr::u32> pos;
    int id;
  };
  struct SRect {
    irr::core::rect<irr::u32> pos;
    int children[2];
    bool packed;
    int id;
    bool operator<(const SRect & other) const {
      return pos.getArea() > other.pos.getArea();
    }
  };

  void pack(const irr::core::array<irr::core::rect<irr::u32>> &rects, irr::core::array<irr::core::array<SPacked>> &packed, irr::u32 sizeOfPack);
  void clear();
  void fill(int pack);
  void split(int pack, int rect);
  bool fits(SRect rect1, SRect rect2);
  void addPackToArray(int pack, irr::core::array<SPacked> &addArray) const;

  bool isRectValid(int i) const;
  bool isPackValid(int i) const;

  int mPackSize;
  int mNumPacked;
  irr::core::array<SRect> mRects;
  irr::core::array<SRect> mPacks;
  irr::core::array<int> mRoots;
};

static int globalPackedTextureCount = 0;

enum TEXTURE_PADDING_TECHNIQUE {
  ETPT_EXPAND = 0,
  ETPT_TILE = 1
};

class	CMeshCombiner {
public:
  CMeshCombiner();
  irr::core::dimension2du	findOptimalPackingArea(irr::core::array<irr::core::rect<irr::u32>> rectangles);
  irr::video::ITexture		*packTextures(irr::video::IVideoDriver* driver,
					      irr::core::array<irr::video::ITexture*> textures,
					      irr::core::array<irr::core::position2di> &outPositions);
  irr::scene::IMesh		*combineMeshes(irr::scene::ISceneManager* smgr,
					       irr::core::array<irr::scene::IMeshSceneNode*> nodes,
					       const irr::core::stringc & meshNameInCache,
					       bool clearNodesAfterUse = true,
					       bool useHardwareMappingHint = true);

  void				setSizingTolerance(irr::f32 tolerance);
  void				setTexturePaddingTechnique(TEXTURE_PADDING_TECHNIQUE technique);

  irr::f32			getSizingTolerance();
  TEXTURE_PADDING_TECHNIQUE	getTexturePaddingTechnique();

private:
  irr::f32			mSizingTolerance;
  TEXTURE_PADDING_TECHNIQUE	mTexturePaddingTechnique;
};

#endif /* !CMESHCOMBINER_HH_ */
