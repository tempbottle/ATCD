// $Id$

#include "ciao/CIAO_common.h"
#include "CCD_Handler.h"
#include "ccd.hpp"
#include "Property_Handler.h"
#include "CPD_Handler.h"
#include "ComponentPropertyDescription_Handler.h"
#include "ciao/Deployment_DataC.h"

namespace CIAO
{
  namespace Config_Handlers
  {
    void
    CCD_Handler::component_interface_descr (
                                            const ComponentInterfaceDescription &desc,
                                            Deployment::ComponentInterfaceDescription& toconfig)
    {
      CIAO_TRACE("CCD_Handler::component_interface_descr");
      if (desc.UUID_p ())
        toconfig.UUID =
          CORBA::string_dup (desc.UUID ().c_str ());

      if (desc.label_p ())
        {
          toconfig.label =
            CORBA::string_dup (desc.label ().c_str ());
        }

      if (desc.specificType_p ())
        {
          toconfig.specificType =
            CORBA::string_dup (desc.specificType ().c_str ());
        }

      ComponentInterfaceDescription::supportedType_const_iterator
        end = desc.end_supportedType ();

      CORBA::ULong pos = 0;
      toconfig.supportedType.length (desc.count_supportedType ());
      for (ComponentInterfaceDescription::supportedType_const_iterator s =
             desc.begin_supportedType ();
           s != end;
           ++s)
        {
          toconfig.supportedType[pos++] = s->c_str ();
        }

      ComponentInterfaceDescription::idlFile_const_iterator
        eidl = desc.end_idlFile ();
      pos = 0;
      toconfig.idlFile.length (desc.count_idlFile ());
      for (ComponentInterfaceDescription::idlFile_const_iterator sidl=
             desc.begin_idlFile ();
           sidl != eidl;
           ++sidl)
        {
          toconfig.idlFile [pos++] = sidl->c_str ();
        }

      ComponentInterfaceDescription::configProperty_const_iterator pend =
        desc.end_configProperty ();
      pos = 0;
      toconfig.configProperty.length (desc.count_configProperty ());
      for (ComponentInterfaceDescription::configProperty_const_iterator pstart =
             desc.begin_configProperty ();
           pstart != pend;
           ++pstart)
        {
          Property_Handler::get_property (*pstart,
                                          toconfig.configProperty [pos++]);
        }

      pos = 0;
      toconfig.port.length (desc.count_port ());
      for (ComponentInterfaceDescription::port_const_iterator
             port (desc.begin_port ());
           port != desc.end_port ();
           ++port)
        {
          CPD_Handler::component_port_description (
                                                   *port,
                                                   toconfig.port[pos++]);
        }

      pos = 0;
      toconfig.property.length ( desc.count_property ());
      for(ComponentInterfaceDescription::property_const_iterator
            prop (desc.begin_property());
          prop != desc.end_property();
          prop++)
        {
          ComponentPropertyDescription_Handler::component_property_description (
                                                                                *prop,
                                                                                toconfig.property[pos++]);
        }

      pos = 0;
      toconfig.infoProperty.length (desc.count_infoProperty ());
      for ( ComponentInterfaceDescription::infoProperty_const_iterator
              infoProp (desc.begin_infoProperty());
            infoProp != desc.end_infoProperty();
            infoProp++)
        {
          Property_Handler::get_property (
                                          *infoProp,
                                          toconfig.infoProperty[pos]);
        }
    }

    ComponentInterfaceDescription
    CCD_Handler::component_interface_descr (
                                            const ::Deployment::ComponentInterfaceDescription&  src)
    {
      CIAO_TRACE("CCD_Handler::component_interface_descr - reverse");
      ComponentInterfaceDescription cid;

      //Load up the basic string members
      XMLSchema::string< char > uuid ((src.UUID));
      XMLSchema::string< char > label ((src.label));
      XMLSchema::string< char > specifict ((src.specificType));

      //Then put them in the CID
      cid.UUID (uuid);
      cid.label (label);
      cid.specificType (specifict);

      //Get the supported type(s) and load them into cid
      ::CORBA::ULong total = src.supportedType.length ();
      for (size_t i = 0; i < total; ++i)
        {
          XMLSchema::string< char > curr ((src.supportedType[i]));
          cid.add_supportedType (curr);
        }

      //Get the idlFile(s) and store them into the cid
      total = src.idlFile.length ();
      for (size_t j = 0; j < total; ++j)
        {
          XMLSchema::string< char > curr ((src.idlFile[j]));
          cid.add_idlFile (curr);
        }

      //Get the configProperty(ies) and store them into the cid
      total = src.configProperty.length ();
      for (size_t k = 0; k < total; ++k)
        {
          cid.add_configProperty (
                                  Property_Handler::get_property (src.configProperty[k]));
        }

      //Same drill for the component port description(s)
      total = src.port.length ();
      for (size_t l = 0; l < total; ++l)
        {
          cid.add_port (
                        CPD_Handler::component_port_description (src.port[l]));
        }

      //Load up the property field
      total = src.property.length();
      for(size_t m = 0;
          m < total;
          m++)
        {
          cid.add_property(
                           ComponentPropertyDescription_Handler::component_property_description (
                                                                                                 src.property[m]));
        }

      //Load up the infoProperty(s)
      total = src.infoProperty.length();
      for(size_t n = 0;
          n < total;
          n++)
        {
          cid.add_infoProperty(
                               Property_Handler::get_property (src.infoProperty[n]));
        }

      return cid;
    }
  }
}
