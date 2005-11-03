// $Id$

#include "Connect.h"
#include "Consumer.h"
#include "Supplier.h"
#include "orbsvcs/Event/EC_Event_Channel.h"
#include "ace/Arg_Shifter.h"
#include "ace/Argv_Type_Converter.h"
#include "ace/High_Res_Timer.h"
#include "ace/OS_NS_strings.h"

ACE_RCSID (EC_Tests_Performance,
           Connect,
           "$Id$")

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_Argv_Type_Converter convert (argc, argv);

  EC_Connect driver;
  return driver.run (argc, argv);
}

// ****************************************************************

EC_Connect::EC_Connect (void)
  : order_ (0)
{
}

void
EC_Connect::execute_test (ACE_ENV_SINGLE_ARG_DECL_NOT_USED)
{
  // this->EC_Driver::execute_test (ACE_ENV_SINGLE_ARG_PARAMETER);
}

int
EC_Connect::parse_args (int& argc, ACE_TCHAR* argv[])
{
  if (this->EC_Driver::parse_args (convert.get_argc(), convert.get_ASCII_argv()) != 0)
    return -1;

  ACE_TArg_Shifter< char > arg_shifter (argc, argv);

  while (arg_shifter.is_anything_left ())
    {
      const char *arg = arg_shifter.get_current ();

      if (ACE_OS::strcmp (arg, "-connection_order") == 0)
        {
          arg_shifter.consume_arg ();

          if (arg_shifter.is_parameter_next ())
            {
              const char* opt = arg_shifter.get_current ();
              if (ACE_OS::strcasecmp (opt, "consumers") == 0)
                this->order_ = 0;
              else if (ACE_OS::strcasecmp (opt, "suppliers") == 0)
                this->order_ = 1;
              else if (ACE_OS::strcasecmp (opt, "interleaved") == 0)
                this->order_ = 2;
              else
                ACE_ERROR ((LM_ERROR,
                            "EC_Connect - invalid choice <%s> for"
                            " connection order\n",
                            opt));

              arg_shifter.consume_arg ();
            }
        }

      else
        {
          arg_shifter.ignore_arg ();
        }
    }
  return 0;
}

void
EC_Connect::print_usage (void)
{
  this->EC_Driver::print_usage ();

  ACE_DEBUG ((LM_DEBUG,
              "EC_Connect Usage:\n"
              "  -connection_order [consumers|suppliers|interleaved]\n"
              ));
}

void
EC_Connect::print_args (void) const
{
  this->EC_Driver::print_args ();

  ACE_DEBUG ((LM_DEBUG,
              "EC_Connect parameters:\n"
              "  order = <%d>\n",
              this->order_));
}

void
EC_Connect::dump_results (void)
{
  ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
  ACE_DEBUG ((LM_DEBUG, "\nConnect time:\n"));
  this->consumer_connect_.dump_results ("Consumer/connect", gsf);
  this->supplier_connect_.dump_results ("Supplier/connect", gsf);

  ACE_DEBUG ((LM_DEBUG, "\nDisconnect time:\n"));
}

void
EC_Connect::connect_consumer (
    RtecEventChannelAdmin::ConsumerAdmin_ptr consumer_admin,
    int i
    ACE_ENV_ARG_DECL)
{
  ACE_hrtime_t start = ACE_OS::gethrtime ();
  this->EC_Driver::connect_consumer (consumer_admin,
                                     i
                                     ACE_ENV_ARG_PARAMETER);
  ACE_hrtime_t now = ACE_OS::gethrtime ();
  this->consumer_connect_.sample (now - this->start_time_,
                                  now - start);
}

void
EC_Connect::connect_supplier (
    RtecEventChannelAdmin::SupplierAdmin_ptr supplier_admin,
    int i
    ACE_ENV_ARG_DECL)
{
  ACE_hrtime_t start = ACE_OS::gethrtime ();
  this->EC_Driver::connect_supplier (supplier_admin,
                                     i
                                     ACE_ENV_ARG_PARAMETER);
  ACE_hrtime_t now = ACE_OS::gethrtime ();
  this->supplier_connect_.sample (now - this->start_time_,
                                  now - start);
}

EC_Consumer*
EC_Connect::allocate_consumer (int i)
{
  return new ECC_Consumer (this, this->consumers_ + i);
}

EC_Supplier*
EC_Connect::allocate_supplier (int i)
{
  return new ECC_Supplier (this, this->consumers_ + i);
}

void
EC_Connect::connect_clients (ACE_ENV_SINGLE_ARG_DECL)
{
  this->start_time_ = ACE_OS::gethrtime ();
  switch (this->order_)
    {
    default:
    case 0:
      this->connect_consumers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      this->connect_suppliers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      return;

    case 1:
      this->connect_suppliers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      this->connect_consumers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      return;

    case 2:
      break;
    }

  int max = this->n_consumers_;
  if (max < this->n_suppliers_)
    max = this->n_suppliers_;

  RtecEventChannelAdmin::ConsumerAdmin_var consumer_admin =
    this->event_channel_->for_consumers (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK;

  RtecEventChannelAdmin::SupplierAdmin_var supplier_admin =
    this->event_channel_->for_suppliers (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK;

  for (int i = 0; i != max; ++i)
    {
      if (i < this->n_consumers_)
        {
          this->connect_consumer (consumer_admin.in (), i ACE_ENV_ARG_PARAMETER);
          ACE_CHECK;
        }
      if (i < this->n_suppliers_)
        {
          this->connect_supplier (supplier_admin.in (), i ACE_ENV_ARG_PARAMETER);
          ACE_CHECK;
        }
    }

}

void
EC_Connect::disconnect_clients (ACE_ENV_SINGLE_ARG_DECL)
{
  switch (this->order_)
    {
    default:
    case 0:
      this->disconnect_suppliers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      this->disconnect_consumers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      return;

    case 1:
      this->disconnect_consumers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      this->disconnect_suppliers (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;
      return;

    case 2:
      break;
    }

  int max = this->n_consumers_;
  if (max < this->n_suppliers_)
    max = this->n_suppliers_;

  RtecEventChannelAdmin::ConsumerAdmin_var consumer_admin =
    this->event_channel_->for_consumers (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK;

  RtecEventChannelAdmin::SupplierAdmin_var supplier_admin =
    this->event_channel_->for_suppliers (ACE_ENV_SINGLE_ARG_PARAMETER);
  ACE_CHECK;

  ACE_hrtime_t start_time = ACE_OS::gethrtime ();
  for (int i = 0; i != max; ++i)
    {
      if (i < this->n_suppliers_)
        {
          ACE_hrtime_t start = ACE_OS::gethrtime ();

          this->suppliers_[i]->disconnect (ACE_ENV_SINGLE_ARG_PARAMETER);
          ACE_CHECK;

          ACE_hrtime_t now = ACE_OS::gethrtime ();
          this->supplier_disconnect_.sample (now - start_time,
                                             now - start);
        }
      if (i < this->n_consumers_)
        {
          ACE_hrtime_t start = ACE_OS::gethrtime ();

          this->consumers_[i]->disconnect (ACE_ENV_SINGLE_ARG_PARAMETER);
          ACE_CHECK;

          ACE_hrtime_t now = ACE_OS::gethrtime ();
          this->consumer_disconnect_.sample (now - start_time,
                                             now - start);
        }
    }
  ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
  this->consumer_disconnect_.dump_results ("Consumer/disconnect", gsf);
  this->supplier_disconnect_.dump_results ("Supplier/disconnect", gsf);
}

void
EC_Connect::disconnect_consumers (ACE_ENV_SINGLE_ARG_DECL)
{
  ACE_hrtime_t start_time = ACE_OS::gethrtime ();
  for (int i = 0; i < this->n_consumers_; ++i)
    {
      ACE_hrtime_t start = ACE_OS::gethrtime ();

      this->consumers_[i]->disconnect (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;

      ACE_hrtime_t now = ACE_OS::gethrtime ();
      this->consumer_disconnect_.sample (now - start_time,
                                         now - start);
    }
  ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
  this->consumer_disconnect_.dump_results ("Consumer/disconnect",
                                           gsf);
  if (this->verbose ())
    ACE_DEBUG ((LM_DEBUG, "EC_Connect (%P|%t) consumers disconnected\n"));
}

void
EC_Connect::disconnect_suppliers (ACE_ENV_SINGLE_ARG_DECL)
{
  ACE_hrtime_t start_time = ACE_OS::gethrtime ();
  for (int i = 0; i < this->n_suppliers_; ++i)
    {
      ACE_hrtime_t start = ACE_OS::gethrtime ();

      this->suppliers_[i]->disconnect (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK;

      ACE_hrtime_t now = ACE_OS::gethrtime ();
      this->supplier_disconnect_.sample (now - start_time,
                                         now - start);
    }
  ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
  this->supplier_disconnect_.dump_results ("Supplier/disconnect",
                                           gsf);
  if (this->verbose ())
    ACE_DEBUG ((LM_DEBUG, "EC_Connect (%P|%t) suppliers disconnected\n"));
}


// ****************************************************************

ECC_Consumer::ECC_Consumer (EC_Driver* driver, void* cookie)
  :  EC_Consumer (driver, cookie)
{
}

void
ECC_Consumer::connect (
    RtecEventChannelAdmin::ConsumerAdmin_ptr consumer_admin,
    const RtecEventChannelAdmin::ConsumerQOS& qos,
    int shutdown_event_type
    ACE_ENV_ARG_DECL)
{
  this->EC_Consumer::connect (consumer_admin,
                              qos,
                              shutdown_event_type
                              ACE_ENV_ARG_PARAMETER);
}

void
ECC_Consumer::connect (
    const RtecEventChannelAdmin::ConsumerQOS& qos,
    int shutdown_event_type
    ACE_ENV_ARG_DECL)
{
  ACE_hrtime_t start = ACE_OS::gethrtime ();
  this->EC_Consumer::connect (qos,
                              shutdown_event_type
                              ACE_ENV_ARG_PARAMETER);
  ACE_hrtime_t now = ACE_OS::gethrtime ();
  this->connect_time_.sample (now, now - start);
}

void
ECC_Consumer::dump_results (const char* name,
                            ACE_UINT32 gsf)
{
  this->connect_time_.dump_results (name, gsf);
  this->EC_Consumer::dump_results (name, gsf);
}

// ****************************************************************

ECC_Supplier::ECC_Supplier (EC_Driver* driver, void* cookie)
  :  EC_Supplier (driver, cookie)
{
}

void
ECC_Supplier::connect (
    RtecEventChannelAdmin::SupplierAdmin_ptr supplier_admin,
    const RtecEventChannelAdmin::SupplierQOS& qos,
    int shutdown_event_type
    ACE_ENV_ARG_DECL)
{
  this->EC_Supplier::connect (supplier_admin,
                              qos,
                              shutdown_event_type
                              ACE_ENV_ARG_PARAMETER);
}

void
ECC_Supplier::connect (
    const RtecEventChannelAdmin::SupplierQOS& qos,
    int shutdown_event_type
    ACE_ENV_ARG_DECL)
{
  ACE_hrtime_t start = ACE_OS::gethrtime ();
  this->EC_Supplier::connect (qos,
                              shutdown_event_type
                              ACE_ENV_ARG_PARAMETER);
  ACE_hrtime_t now = ACE_OS::gethrtime ();
  this->connect_time_.sample (now, now - start);
}

void
ECC_Supplier::dump_results (const char* name,
                            ACE_UINT32 gsf)
{
  this->connect_time_.dump_results (name, gsf);
  this->EC_Supplier::dump_results (name, gsf);
}
