#ifndef PROTON_CPP_CONTAINER_H
#define PROTON_CPP_CONTAINER_H

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#include "proton/cpp/ImportExport.h"
#include "proton/cpp/Handle.h"
#include "proton/cpp/Acceptor.h"
#include "proton/cpp/Duration.h"
#include <proton/reactor.h>
#include <string>

namespace proton {
namespace reactor {

class DispatchHelper;
class Connection;
class Connector;
class Acceptor;
class ContainerImpl;
class MessagingHandler;
class Sender;
class Receiver;
class Link;
 class Handler;

class Container : public Handle<ContainerImpl>
{
  public:
    PROTON_CPP_EXTERN Container(ContainerImpl *);
    PROTON_CPP_EXTERN Container(const Container& c);
    PROTON_CPP_EXTERN Container& operator=(const Container& c);
    PROTON_CPP_EXTERN ~Container();

    PROTON_CPP_EXTERN Container();
    PROTON_CPP_EXTERN Container(MessagingHandler &mhandler);
    PROTON_CPP_EXTERN Connection connect(std::string &host, Handler *h=0);
    PROTON_CPP_EXTERN void run();
    PROTON_CPP_EXTERN void start();
    PROTON_CPP_EXTERN bool process();
    PROTON_CPP_EXTERN void stop();
    PROTON_CPP_EXTERN void wakeup();
    PROTON_CPP_EXTERN bool isQuiesced();
    PROTON_CPP_EXTERN pn_reactor_t *getReactor();
    PROTON_CPP_EXTERN Sender createSender(Connection &connection, std::string &addr, Handler *h=0);
    PROTON_CPP_EXTERN Sender createSender(std::string &url);
    PROTON_CPP_EXTERN Receiver createReceiver(Connection &connection, std::string &addr);
    PROTON_CPP_EXTERN Receiver createReceiver(const std::string &url);
    PROTON_CPP_EXTERN Acceptor listen(const std::string &url);
    PROTON_CPP_EXTERN std::string getContainerId();
    PROTON_CPP_EXTERN Duration getTimeout();
    PROTON_CPP_EXTERN void setTimeout(Duration timeout);
  private:
   friend class PrivateImplRef<Container>;
};

}} // namespace proton::reactor

#endif  /*!PROTON_CPP_CONTAINER_H*/
