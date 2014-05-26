#ifndef _CCB_CCBMEMBERVARIABLEASSIGNER_H_
#define _CCB_CCBMEMBERVARIABLEASSIGNER_H_


namespace cocosbuilder {

#define CCB_MEMBERVARIABLEASSIGNER_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if (pTarget == TARGET && 0 == strcmp(pMemberVariableName, (MEMBERVARIABLENAME))) { \
        MEMBERVARIABLETYPE pOldVar = MEMBERVARIABLE; \
        MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(MEMBERVARIABLE); \
        if (pOldVar != MEMBERVARIABLE) { \
            CC_SAFE_RELEASE(pOldVar); \
            MEMBERVARIABLE->retain(); \
        } \
        return true; \
    }

#define CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLETYPE, MEMBERVARIABLE) \
    if (pTarget == TARGET && 0 == strcmp(pMemberVariableName, MEMBERVARIABLENAME)) { \
        MEMBERVARIABLE = dynamic_cast<MEMBERVARIABLETYPE>(pNode); \
        CC_ASSERT(MEMBERVARIABLE); \
        return true; \
    }

class CCBMemberVariableAssigner {
    public:
        /**
         * @js NA
         * @lua NA
         */
        virtual ~CCBMemberVariableAssigner() {};

        /**
         *  设施成员变量的回调函数
         *  @note 成员变量必须是Node或Node的子类
         *  @param target               自定义的类
         *  @param memberVariableName   成员变量的名称
         *  @param node                 成员变量
         *  @return 成功返回true
         */
        virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node) = 0;

        /**
         *  设置自定义属性的回调函数。
         *  @note 成员变量必须是Integer, Float, Boolean 或 String.
         *  @param target               自定义类
         *  @param memberVariableName   成员变量的名称
         *  @param value                属性的值
         *  @return 成功返回true
         */
        virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value) { return false; };
};

}

#endif
