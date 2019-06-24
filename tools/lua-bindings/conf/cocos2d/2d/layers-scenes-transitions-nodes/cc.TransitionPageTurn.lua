local cls = class()
cls.CPPCLS = "cocos2d::TransitionPageTurn"
cls.LUACLS = "cc.TransitionPageTurn"
cls.SUPERCLS = "cc.TransitionScene"
cls.funcs([[
    static TransitionPageTurn* create(float t, @ref(map autoref) Scene* scene,bool backwards)
    ActionInterval* actionWithSize(const Size& vector)
]])

return cls