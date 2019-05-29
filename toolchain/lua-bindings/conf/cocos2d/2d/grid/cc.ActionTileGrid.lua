local M = {}

local cls = class(M)
cls.CPPCLS = "cocos2d::ShakyTiles3D"
cls.LUACLS = "cc.ShakyTiles3D"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static ShakyTiles3D* create(float duration, const Size& gridSize, int range, bool shakeZ)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::ShatteredTiles3D"
cls.LUACLS = "cc.ShatteredTiles3D"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static ShatteredTiles3D* create(float duration, const Size& gridSize, int range, bool shatterZ)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::ShuffleTiles"
cls.LUACLS = "cc.ShuffleTiles"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static ShuffleTiles* create(float duration, const Size& gridSize, unsigned int seed)
    // void shuffle(unsigned int *array, unsigned int len)
    Size getDelta(const Size& pos)
    // void placeTile(const Vec2& pos, Tile *t)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::FadeOutTRTiles"
cls.LUACLS = "cc.FadeOutTRTiles"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static FadeOutTRTiles* create(float duration, const Size& gridSize)
    float testFunc(const Size& pos, float time)
    void turnOnTile(const Vec2& pos)
    void turnOffTile(const Vec2& pos)
    void transformTile(const Vec2& pos, float distance)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::FadeOutBLTiles"
cls.LUACLS = "cc.FadeOutBLTiles"
cls.SUPERCLS = "cc.FadeOutTRTiles"
cls.funcs [[
    static FadeOutBLTiles* create(float duration, const Size& gridSize)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::FadeOutUpTiles"
cls.LUACLS = "cc.FadeOutUpTiles"
cls.SUPERCLS = "cc.FadeOutTRTiles"
cls.funcs [[
    static FadeOutUpTiles* create(float duration, const Size& gridSize)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::FadeOutDownTiles"
cls.LUACLS = "cc.FadeOutDownTiles"
cls.SUPERCLS = "cc.FadeOutUpTiles"
cls.funcs [[
    static FadeOutDownTiles* create(float duration, const Size& gridSize)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::TurnOffTiles"
cls.LUACLS = "cc.TurnOffTiles"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static TurnOffTiles* create(float duration, const Size& gridSize)
    static TurnOffTiles* create(float duration, const Size& gridSize, unsigned int seed)
    // void shuffle(unsigned int *array, unsigned int len)
    void turnOnTile(const Vec2& pos)
    void turnOffTile(const Vec2& pos)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::WavesTiles3D"
cls.LUACLS = "cc.WavesTiles3D"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static WavesTiles3D* create(float duration, const Size& gridSize, unsigned int waves, float amplitude)
    float getAmplitude()
    void setAmplitude(float amplitude)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::JumpTiles3D"
cls.LUACLS = "cc.JumpTiles3D"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static JumpTiles3D* create(float duration, const Size& gridSize, unsigned int numberOfJumps, float amplitude)
    float getAmplitude()
    void setAmplitude(float amplitude)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::SplitRows"
cls.LUACLS = "cc.SplitRows"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static SplitRows* create(float duration, unsigned int rows)
]]

local cls = class(M)
cls.CPPCLS = "cocos2d::SplitCols"
cls.LUACLS = "cc.SplitCols"
cls.SUPERCLS = "cc.TiledGrid3DAction"
cls.funcs [[
    static SplitCols* create(float duration, unsigned int cols)
]]

return M