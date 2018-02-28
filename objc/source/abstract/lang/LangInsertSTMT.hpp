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

#ifndef LangInsertSTMT_hpp
#define LangInsertSTMT_hpp

#include <WCDB/LangCommon.h>

namespace WCDB {

namespace Lang {

class InsertSTMT : public CRUDLang {
public:
    InsertSTMT();

    CopyOnWriteLazyLang<WithClause> withClause;

    enum class Type : int {
        NotSet,
        Insert,
        InsertOrReplace,
        InsertOrRollback,
        InsertOrAbort,
        InsertOrFail,
        InsertOrIgnore,
    };
    Type type;

    CopyOnWriteString schemaName;
    CopyOnWriteString tableName;

    CopyOnWriteLazyLangList<Column> columns;

    enum class Switch : int {
        NotSet,
        Values,
        Select,
        DefaultValues,
    };
    Switch switcher;

    CopyOnWriteLazyLangList<Expr> exprs;
    CopyOnWriteLazyLang<SelectSTMT> selectSTMT;

    virtual CopyOnWriteString SQL() const override;

protected:
    static constexpr const char *TypeName(const Type &type);
};

} // namespace Lang

} // namespace WCDB

#endif /* LangInsertSTMT_hpp */
