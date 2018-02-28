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

#ifndef LangExpr_hpp
#define LangExpr_hpp

#include <WCDB/LangCommon.h>

namespace WCDB {

namespace Lang {

class ExprBase : public Lang {
};
class ExprColumn;
class ExprUnaryOperation;
class ExprBinaryOperation;
class ExprFunction;
class ExprList;
class ExprCast;
class ExprCollate;
class ExprPattern;
class ExprNull;
class ExprBetween;
class ExprIn;
class ExprExists;
class ExprCase;
class Expr;

class ExprColumn : public ExprBase {
public:
    CopyOnWriteString schemaName;
    CopyOnWriteString tableName;
    CopyOnWriteLazyLang<Column> column;

    virtual CopyOnWriteString SQL() const override;
};

class ExprUnaryOperation : public ExprBase {
public:
    enum class Operator : int {
        Negative,
        Positive,
        Tilde,
        Not,
    };
    Operator unaryOperator;
    CopyOnWriteLazyLang<ExprBase> expr;

    virtual CopyOnWriteString SQL() const override;

private:
    static constexpr const char *OperatorName(const Operator &unaryOpeartor);
};

class ExprBinaryOperation : public ExprBase {
public:
    enum class Operator : int {
        Concatenate,
        Multiply,
        Divide,
        Modulo,
        Plus,
        Minus,
        LeftShift,
        RightShift,
        BitwiseAnd,
        BitwiseOr,
        Less,
        LessOrEqual,
        Greater,
        GreaterOrEqual,
        Equal,
        NotEqual,
        Is,
        IsNot,
        And,
        Or,
    };
    CopyOnWriteLazyLang<ExprBase> left;
    CopyOnWriteLazyLang<ExprBase> right;
    Operator binaryOperator;

    virtual CopyOnWriteString SQL() const override;

private:
    static constexpr const char *OperatorName(const Operator &binaryOpeartor);
};

class ExprFunction : public ExprBase {
public:
    CopyOnWriteString functionName;
    enum class Type : int {
        NotSet,
        Expr,
        DistinctExpr,
        Star,
    };
    Type type;
    CopyOnWriteLazyLangList<ExprBase> exprs;

    virtual CopyOnWriteString SQL() const override;
};

class ExprList : public ExprBase {
public:
    CopyOnWriteLazyLangList<ExprBase> exprs;

    virtual CopyOnWriteString SQL() const override;
};

class ExprCast : public ExprBase {
public:
    CopyOnWriteLazyLang<ExprBase> expr;
    ColumnType type;

    virtual CopyOnWriteString SQL() const override;
};

class ExprCollate : public ExprBase {
public:
    CopyOnWriteLazyLang<ExprBase> expr;
    CopyOnWriteString collationName;

    virtual CopyOnWriteString SQL() const override;
};

class ExprPattern : public ExprBase {
public:
    bool isNot;
    CopyOnWriteLazyLang<ExprBase> left;
    enum class Type : int {
        Like,
        Glob,
        Regexp,
        Match,
    };
    Type type;
    CopyOnWriteLazyLang<ExprBase> right;
    CopyOnWriteLazyLang<ExprBase> escape;

    virtual CopyOnWriteString SQL() const override;

protected:
    static constexpr const char *TypeName(const Type &type);
};

class ExprNull : public ExprBase {
public:
    CopyOnWriteLazyLang<ExprBase> expr;
    bool isNull;

    virtual CopyOnWriteString SQL() const override;
};

class ExprBetween : public ExprBase {
public:
    bool isNot;
    CopyOnWriteLazyLang<ExprBase> expr;
    CopyOnWriteLazyLang<ExprBase> left;
    CopyOnWriteLazyLang<ExprBase> right;

    virtual CopyOnWriteString SQL() const override;
};

class ExprIn : public ExprBase {
public:
    bool isNot;
    CopyOnWriteLazyLang<ExprBase> expr;

    enum class Switch : int {
        NotSet,
        Select,
        Expr,
        Table,
        Function,
    };
    Switch switcher;

    CopyOnWriteLazyLang<SelectSTMT> selectSTMT;
    CopyOnWriteLazyLangList<ExprBase> exprs;
    CopyOnWriteString schemaName;
    CopyOnWriteString tableNameOrFunction;

    virtual CopyOnWriteString SQL() const override;
};

class ExprExists : public ExprBase {
public:
    bool exists;
    bool isNot;
    CopyOnWriteLazyLang<SelectSTMT> selectSTMT;

    virtual CopyOnWriteString SQL() const override;
};

class ExprCase : public ExprBase {
public:
    CopyOnWriteLazyLang<ExprBase> exprCase;

    class Pair : public Lang {
    public:
        CopyOnWriteLazyLang<ExprBase> when;
        CopyOnWriteLazyLang<ExprBase> then;

        virtual CopyOnWriteString SQL() const override;
    };

    CopyOnWriteLazyLangList<Pair> pairs;

    CopyOnWriteLazyLang<ExprBase> exprElse;

    virtual CopyOnWriteString SQL() const override;
};

template <>
CopyOnWriteString
CopyOnWriteLazyLangList<ExprCase::Pair>::calculatedDescription() const;

class Expr : public ExprBase {
public:
    Expr();

    enum class Type : int {
        NotSet,
        LiteralValue,
        BindParameter,
        Column,
        UnaryOperator,
        BinaryOperator,
        Function,
        List,
        Cast,
        Collate,
        Pattern,
        Null,
        Between,
        In,
        Exists,
        Case,
        RaiseFunction,
    };
    Type type;

    CopyOnWriteLazyLang<LiteralValue> literalValue;
    CopyOnWriteLazyLang<BindParameter> bindParamter;
    CopyOnWriteLazyLang<ExprColumn> exprColumn;
    CopyOnWriteLazyLang<ExprUnaryOperation> exprUnaryOperator;
    CopyOnWriteLazyLang<ExprBinaryOperation> exprBinaryOperator;
    CopyOnWriteLazyLang<ExprFunction> exprFunction;
    CopyOnWriteLazyLang<ExprList> exprList;
    CopyOnWriteLazyLang<ExprCast> exprCast;
    CopyOnWriteLazyLang<ExprCollate> exprCollate;
    CopyOnWriteLazyLang<ExprPattern> exprPattern;
    CopyOnWriteLazyLang<ExprNull> exprNull;
    CopyOnWriteLazyLang<ExprBetween> exprBetween;
    CopyOnWriteLazyLang<ExprIn> exprIn;
    CopyOnWriteLazyLang<ExprExists> exprExists;
    CopyOnWriteLazyLang<ExprCase> exprCase;
    CopyOnWriteLazyLang<RaiseFunction> raiseFunction;

    virtual CopyOnWriteString SQL() const override;
};

} // namespace Lang

} // namespace WCDB

#endif /* LangExpr_hpp */
