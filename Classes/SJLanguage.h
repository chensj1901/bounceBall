//
//  SJLanguage.h
//  bounceBall
//
//  Created by 陈少杰 on 15/7/18.
//
//

#ifndef __bounceBall__SJLanguage__
#define __bounceBall__SJLanguage__

using namespace cocos2d;

//return type:const char*
#define LocalizedCStringByKey(key) (Language::getStringByKey(key))

class Language{
    
public:
    
    static const char* getStringByKey(const char * key){
        
        //获取当前系统环境语言类型
        ccLanguageType languageType = CCApplication::sharedApplication()->getCurrentLanguage();
        
        //字典
        CCDictionary *pDic;
        
        if(kLanguageChinese == languageType)
            //根据语言选择不同的属性表
            pDic = CCDictionary::createWithContentsOfFile("language/zh.plist");
        else
            pDic = CCDictionary::createWithContentsOfFile("language/en.plist");
        
        std::string keyStr = key;
        
        //返回key对应的value
        return (pDic -> valueForKey(keyStr))->getCString();
    }  
    
};

#endif /* defined(__bounceBall__SJLanguage__) */
