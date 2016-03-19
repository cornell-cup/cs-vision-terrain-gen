// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.5.1
//
// <auto-generated>
//
// Generated from file `VisionModule.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <VisionModule.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 305
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace
{

const ::std::string __VisionModule__VisionInterface__ping_name = "ping";

const ::std::string __VisionModule__VisionInterface__getVision_name = "getVision";

const ::std::string __VisionModule__BaseInterface__ping_name = "ping";

const ::std::string __VisionModule__BaseInterface__update_name = "update";

}

namespace Ice
{
}
::IceProxy::Ice::Object* ::IceProxy::VisionModule::upCast(::IceProxy::VisionModule::VisionInterface* p) { return p; }

void
::IceProxy::VisionModule::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::VisionModule::VisionInterface>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::VisionModule::VisionInterface;
        v->__copyFrom(proxy);
    }
}

::Ice::Double
IceProxy::VisionModule::VisionInterface::ping(::Ice::Double a, ::Ice::Double b, ::Ice::Double c, ::Ice::Double d, ::Ice::Double e, ::Ice::Double f, ::Ice::Double g, ::Ice::Double h, ::Ice::Double i, ::Ice::Double j, ::Ice::Double k, ::Ice::Double l, const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __VisionModule__VisionInterface__ping_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__VisionModule__VisionInterface__ping_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::VisionModule::VisionInterface* __del = dynamic_cast< ::IceDelegate::VisionModule::VisionInterface*>(__delBase.get());
            return __del->ping(a, b, c, d, e, f, g, h, i, j, k, l, __ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::VisionModule::VisionInterface::begin_ping(::Ice::Double a, ::Ice::Double b, ::Ice::Double c, ::Ice::Double d, ::Ice::Double e, ::Ice::Double f, ::Ice::Double g, ::Ice::Double h, ::Ice::Double i, ::Ice::Double j, ::Ice::Double k, ::Ice::Double l, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__VisionModule__VisionInterface__ping_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __VisionModule__VisionInterface__ping_name, __del, __cookie);
    try
    {
        __result->__prepare(__VisionModule__VisionInterface__ping_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__startWriteParams(::Ice::DefaultFormat);
        __os->write(a);
        __os->write(b);
        __os->write(c);
        __os->write(d);
        __os->write(e);
        __os->write(f);
        __os->write(g);
        __os->write(h);
        __os->write(i);
        __os->write(j);
        __os->write(k);
        __os->write(l);
        __result->__endWriteParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::Ice::Double
IceProxy::VisionModule::VisionInterface::end_ping(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __VisionModule__VisionInterface__ping_name);
    ::Ice::Double __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

::VisionModule::VisionData
IceProxy::VisionModule::VisionInterface::getVision(const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __VisionModule__VisionInterface__getVision_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__VisionModule__VisionInterface__getVision_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::VisionModule::VisionInterface* __del = dynamic_cast< ::IceDelegate::VisionModule::VisionInterface*>(__delBase.get());
            return __del->getVision(__ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::VisionModule::VisionInterface::begin_getVision(const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__VisionModule__VisionInterface__getVision_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __VisionModule__VisionInterface__getVision_name, __del, __cookie);
    try
    {
        __result->__prepare(__VisionModule__VisionInterface__getVision_name, ::Ice::Normal, __ctx);
        __result->__writeEmptyParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::VisionModule::VisionData
IceProxy::VisionModule::VisionInterface::end_getVision(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __VisionModule__VisionInterface__getVision_name);
    ::VisionModule::VisionData __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

const ::std::string&
IceProxy::VisionModule::VisionInterface::ice_staticId()
{
    return ::VisionModule::VisionInterface::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::VisionModule::VisionInterface::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::VisionModule::VisionInterface);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::VisionModule::VisionInterface::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::VisionModule::VisionInterface);
}

::IceProxy::Ice::Object*
IceProxy::VisionModule::VisionInterface::__newInstance() const
{
    return new VisionInterface;
}
::IceProxy::Ice::Object* ::IceProxy::VisionModule::upCast(::IceProxy::VisionModule::BaseInterface* p) { return p; }

void
::IceProxy::VisionModule::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::VisionModule::BaseInterface>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::VisionModule::BaseInterface;
        v->__copyFrom(proxy);
    }
}

::Ice::Double
IceProxy::VisionModule::BaseInterface::ping(const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __VisionModule__BaseInterface__ping_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__VisionModule__BaseInterface__ping_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::VisionModule::BaseInterface* __del = dynamic_cast< ::IceDelegate::VisionModule::BaseInterface*>(__delBase.get());
            return __del->ping(__ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::VisionModule::BaseInterface::begin_ping(const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__VisionModule__BaseInterface__ping_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __VisionModule__BaseInterface__ping_name, __del, __cookie);
    try
    {
        __result->__prepare(__VisionModule__BaseInterface__ping_name, ::Ice::Normal, __ctx);
        __result->__writeEmptyParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::Ice::Double
IceProxy::VisionModule::BaseInterface::end_ping(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __VisionModule__BaseInterface__ping_name);
    ::Ice::Double __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

::Ice::Int
IceProxy::VisionModule::BaseInterface::update(const ::VisionModule::VisionData& data, const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __VisionModule__BaseInterface__update_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__VisionModule__BaseInterface__update_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::VisionModule::BaseInterface* __del = dynamic_cast< ::IceDelegate::VisionModule::BaseInterface*>(__delBase.get());
            return __del->update(data, __ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::VisionModule::BaseInterface::begin_update(const ::VisionModule::VisionData& data, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__VisionModule__BaseInterface__update_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __VisionModule__BaseInterface__update_name, __del, __cookie);
    try
    {
        __result->__prepare(__VisionModule__BaseInterface__update_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__startWriteParams(::Ice::DefaultFormat);
        __os->write(data);
        __result->__endWriteParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::Ice::Int
IceProxy::VisionModule::BaseInterface::end_update(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __VisionModule__BaseInterface__update_name);
    ::Ice::Int __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

const ::std::string&
IceProxy::VisionModule::BaseInterface::ice_staticId()
{
    return ::VisionModule::BaseInterface::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::VisionModule::BaseInterface::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::VisionModule::BaseInterface);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::VisionModule::BaseInterface::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::VisionModule::BaseInterface);
}

::IceProxy::Ice::Object*
IceProxy::VisionModule::BaseInterface::__newInstance() const
{
    return new BaseInterface;
}

::Ice::Double
IceDelegateM::VisionModule::VisionInterface::ping(::Ice::Double a, ::Ice::Double b, ::Ice::Double c, ::Ice::Double d, ::Ice::Double e, ::Ice::Double f, ::Ice::Double g, ::Ice::Double h, ::Ice::Double i, ::Ice::Double j, ::Ice::Double k, ::Ice::Double l, const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __VisionModule__VisionInterface__ping_name, ::Ice::Normal, __context, __observer);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(a);
        __os->write(b);
        __os->write(c);
        __os->write(d);
        __os->write(e);
        __os->write(f);
        __os->write(g);
        __os->write(h);
        __os->write(i);
        __os->write(j);
        __os->write(k);
        __os->write(l);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::Ice::Double __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::VisionModule::VisionData
IceDelegateM::VisionModule::VisionInterface::getVision(const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __VisionModule__VisionInterface__getVision_name, ::Ice::Normal, __context, __observer);
    __og.writeEmptyParams();
    bool __ok = __og.invoke();
    ::VisionModule::VisionData __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Double
IceDelegateM::VisionModule::BaseInterface::ping(const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __VisionModule__BaseInterface__ping_name, ::Ice::Normal, __context, __observer);
    __og.writeEmptyParams();
    bool __ok = __og.invoke();
    ::Ice::Double __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Int
IceDelegateM::VisionModule::BaseInterface::update(const ::VisionModule::VisionData& data, const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __VisionModule__BaseInterface__update_name, ::Ice::Normal, __context, __observer);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(data);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::Ice::Int __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::Ice::Double
IceDelegateD::VisionModule::VisionInterface::ping(::Ice::Double a, ::Ice::Double b, ::Ice::Double c, ::Ice::Double d, ::Ice::Double e, ::Ice::Double f, ::Ice::Double g, ::Ice::Double h, ::Ice::Double i, ::Ice::Double j, ::Ice::Double k, ::Ice::Double l, const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::Ice::Double& __result, ::Ice::Double __p_a, ::Ice::Double __p_b, ::Ice::Double __p_c, ::Ice::Double __p_d, ::Ice::Double __p_e, ::Ice::Double __p_f, ::Ice::Double __p_g, ::Ice::Double __p_h, ::Ice::Double __p_i, ::Ice::Double __p_j, ::Ice::Double __p_k, ::Ice::Double __p_l, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_a(__p_a),
            _m_b(__p_b),
            _m_c(__p_c),
            _m_d(__p_d),
            _m_e(__p_e),
            _m_f(__p_f),
            _m_g(__p_g),
            _m_h(__p_h),
            _m_i(__p_i),
            _m_j(__p_j),
            _m_k(__p_k),
            _m_l(__p_l)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::VisionModule::VisionInterface* servant = dynamic_cast< ::VisionModule::VisionInterface*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->ping(_m_a, _m_b, _m_c, _m_d, _m_e, _m_f, _m_g, _m_h, _m_i, _m_j, _m_k, _m_l, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::Ice::Double& _result;
        ::Ice::Double _m_a;
        ::Ice::Double _m_b;
        ::Ice::Double _m_c;
        ::Ice::Double _m_d;
        ::Ice::Double _m_e;
        ::Ice::Double _m_f;
        ::Ice::Double _m_g;
        ::Ice::Double _m_h;
        ::Ice::Double _m_i;
        ::Ice::Double _m_j;
        ::Ice::Double _m_k;
        ::Ice::Double _m_l;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __VisionModule__VisionInterface__ping_name, ::Ice::Normal, __context);
    ::Ice::Double __result;
    try
    {
        _DirectI __direct(__result, a, b, c, d, e, f, g, h, i, j, k, l, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::VisionModule::VisionData
IceDelegateD::VisionModule::VisionInterface::getVision(const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::VisionModule::VisionData& __result, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::VisionModule::VisionInterface* servant = dynamic_cast< ::VisionModule::VisionInterface*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->getVision(_current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::VisionModule::VisionData& _result;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __VisionModule__VisionInterface__getVision_name, ::Ice::Normal, __context);
    ::VisionModule::VisionData __result;
    try
    {
        _DirectI __direct(__result, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::Ice::Double
IceDelegateD::VisionModule::BaseInterface::ping(const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::Ice::Double& __result, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::VisionModule::BaseInterface* servant = dynamic_cast< ::VisionModule::BaseInterface*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->ping(_current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::Ice::Double& _result;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __VisionModule__BaseInterface__ping_name, ::Ice::Normal, __context);
    ::Ice::Double __result;
    try
    {
        _DirectI __direct(__result, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::Ice::Int
IceDelegateD::VisionModule::BaseInterface::update(const ::VisionModule::VisionData& data, const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::Ice::Int& __result, const ::VisionModule::VisionData& __p_data, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_data(__p_data)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::VisionModule::BaseInterface* servant = dynamic_cast< ::VisionModule::BaseInterface*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->update(_m_data, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::Ice::Int& _result;
        const ::VisionModule::VisionData& _m_data;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __VisionModule__BaseInterface__update_name, ::Ice::Normal, __context);
    ::Ice::Int __result;
    try
    {
        _DirectI __direct(__result, data, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::Ice::Object* VisionModule::upCast(::VisionModule::VisionInterface* p) { return p; }

namespace
{
const ::std::string __VisionModule__VisionInterface_ids[2] =
{
    "::Ice::Object",
    "::VisionModule::VisionInterface"
};

}

bool
VisionModule::VisionInterface::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__VisionModule__VisionInterface_ids, __VisionModule__VisionInterface_ids + 2, _s);
}

::std::vector< ::std::string>
VisionModule::VisionInterface::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__VisionModule__VisionInterface_ids[0], &__VisionModule__VisionInterface_ids[2]);
}

const ::std::string&
VisionModule::VisionInterface::ice_id(const ::Ice::Current&) const
{
    return __VisionModule__VisionInterface_ids[1];
}

const ::std::string&
VisionModule::VisionInterface::ice_staticId()
{
    return __VisionModule__VisionInterface_ids[1];
}

::Ice::DispatchStatus
VisionModule::VisionInterface::___ping(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::Ice::Double a;
    ::Ice::Double b;
    ::Ice::Double c;
    ::Ice::Double d;
    ::Ice::Double e;
    ::Ice::Double f;
    ::Ice::Double g;
    ::Ice::Double h;
    ::Ice::Double i;
    ::Ice::Double j;
    ::Ice::Double k;
    ::Ice::Double l;
    __is->read(a);
    __is->read(b);
    __is->read(c);
    __is->read(d);
    __is->read(e);
    __is->read(f);
    __is->read(g);
    __is->read(h);
    __is->read(i);
    __is->read(j);
    __is->read(k);
    __is->read(l);
    __inS.endReadParams();
    ::Ice::Double __ret = ping(a, b, c, d, e, f, g, h, i, j, k, l, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
VisionModule::VisionInterface::___getVision(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    __inS.readEmptyParams();
    ::VisionModule::VisionData __ret = getVision(__current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __VisionModule__VisionInterface_all[] =
{
    "getVision",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "ping"
};

}

::Ice::DispatchStatus
VisionModule::VisionInterface::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__VisionModule__VisionInterface_all, __VisionModule__VisionInterface_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __VisionModule__VisionInterface_all)
    {
        case 0:
        {
            return ___getVision(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
        case 5:
        {
            return ___ping(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
VisionModule::VisionInterface::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
VisionModule::VisionInterface::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
VisionModule::__patch(VisionInterfacePtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::VisionModule::VisionInterfacePtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::VisionModule::VisionInterface::ice_staticId(), v);
    }
}

::Ice::Object* VisionModule::upCast(::VisionModule::BaseInterface* p) { return p; }

namespace
{
const ::std::string __VisionModule__BaseInterface_ids[2] =
{
    "::Ice::Object",
    "::VisionModule::BaseInterface"
};

}

bool
VisionModule::BaseInterface::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__VisionModule__BaseInterface_ids, __VisionModule__BaseInterface_ids + 2, _s);
}

::std::vector< ::std::string>
VisionModule::BaseInterface::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__VisionModule__BaseInterface_ids[0], &__VisionModule__BaseInterface_ids[2]);
}

const ::std::string&
VisionModule::BaseInterface::ice_id(const ::Ice::Current&) const
{
    return __VisionModule__BaseInterface_ids[1];
}

const ::std::string&
VisionModule::BaseInterface::ice_staticId()
{
    return __VisionModule__BaseInterface_ids[1];
}

::Ice::DispatchStatus
VisionModule::BaseInterface::___ping(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    __inS.readEmptyParams();
    ::Ice::Double __ret = ping(__current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
VisionModule::BaseInterface::___update(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::VisionModule::VisionData data;
    __is->read(data);
    __inS.endReadParams();
    ::Ice::Int __ret = update(data, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __VisionModule__BaseInterface_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "ping",
    "update"
};

}

::Ice::DispatchStatus
VisionModule::BaseInterface::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__VisionModule__BaseInterface_all, __VisionModule__BaseInterface_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __VisionModule__BaseInterface_all)
    {
        case 0:
        {
            return ___ice_id(in, current);
        }
        case 1:
        {
            return ___ice_ids(in, current);
        }
        case 2:
        {
            return ___ice_isA(in, current);
        }
        case 3:
        {
            return ___ice_ping(in, current);
        }
        case 4:
        {
            return ___ping(in, current);
        }
        case 5:
        {
            return ___update(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
VisionModule::BaseInterface::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
VisionModule::BaseInterface::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
VisionModule::__patch(BaseInterfacePtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::VisionModule::BaseInterfacePtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::VisionModule::BaseInterface::ice_staticId(), v);
    }
}
