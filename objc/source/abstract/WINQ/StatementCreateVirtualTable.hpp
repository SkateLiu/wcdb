/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef StatementCreateVirtualTable_hpp
#define StatementCreateVirtualTable_hpp

#include <WCDB/Describable.hpp>
#include <WCDB/Statement.hpp>

namespace WCDB {

class StatementCreateVirtualTable
    : public StatementWithLang<Lang::CreateVirtualTableSTMT> {
public:
    StatementCreateVirtualTable();
    StatementCreateVirtualTable &
    createVirtualTable(const std::string &tableName);
    StatementCreateVirtualTable &withSchema(const std::string &schemaName);
    StatementCreateVirtualTable &ifNotExists(bool ifNotExists = true);
    StatementCreateVirtualTable &usingModule(const std::string &moduleName);
    StatementCreateVirtualTable &on(const ModuleArgument &moduleArgument);
    StatementCreateVirtualTable &
    on(const std::list<ModuleArgument> &moduleArguments);
    virtual Type getType() const override;
};

} // namespace WCDB

#endif /* StatementCreateVirtualTable_hpp */
