/**
xwiimotelibBuilder header file.
*/

#ifndef XWIIMOTELIB_XWIIMOTELIBBUILDER_H
#define XWIIMOTELIB_XWIIMOTELIBBUILDER_H

#include <CDPSystem/Application/CDPBuilder.h>

namespace xwiimotelib {

class xwiimotelibBuilder : public CDPBuilder
{
public:
  xwiimotelibBuilder(const char* libName);
  CDPComponent* CreateNewComponent(const std::string& type) override;
  CDPBaseObject* CreateNewCDPOperator(const std::string& modelName,const std::string& type,const CDPPropertyBase* inputProperty) override;
  CDPObject* CreateNewObject(const std::string& type) override;
  CDP::StudioAPI::CDPNode* CreateNewCDPNode(const std::string& type) override;
};

}

#endif
