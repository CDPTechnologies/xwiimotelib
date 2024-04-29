/**
xwiimotelibBuilder implementation.
*/

#include "xwiimoteIO.h"
#include "xwiimotelibBuilder.h"

using namespace xwiimotelib;

/*!
  \inmodule xwiimotelib
  \namespace xwiimotelib

  \brief Contains xwiimotelib implementation classes.
  Click into each class to see the documentation for that class, or search for a keyword in the help documentation.
*/

/**
\internal
Do not edit. Autogenerated Builder constructor.
*/
xwiimotelibBuilder::xwiimotelibBuilder(const char* libName)
  : CDPBuilder(libName, __DATE__ " " __TIME__)
{
}

/**
\internal
Do not edit. Autogenerated Builder CDPComponent factory function.
*/
CDPComponent* xwiimotelibBuilder::CreateNewComponent(const std::string& type)
{
    
    if (type=="xwiimotelib.xwiimoteIO")
        return new xwiimoteIO;
    
    return CDPBuilder::CreateNewComponent(type);
}

/**
\internal
Do not edit. Autogenerated Builder CDPBaseObject factory function.
*/
CDPBaseObject* xwiimotelibBuilder::CreateNewCDPOperator(const std::string& modelName, const std::string& type, const CDPPropertyBase* inputProperty)
{
  return CDPBuilder::CreateNewCDPOperator(modelName, type, inputProperty);
}

/**
\internal
Do not edit. Autogenerated Builder CDPObject factory function.
*/
CDPObject* xwiimotelibBuilder::CreateNewObject(const std::string& type)
{
  return CDPBuilder::CreateNewObject(type);
}

/**
\internal
CDPNode factory function.
*/
CDP::StudioAPI::CDPNode* xwiimotelibBuilder::CreateNewCDPNode(const std::string& type)
{
  return CDPBuilder::CreateNewCDPNode(type);
}
