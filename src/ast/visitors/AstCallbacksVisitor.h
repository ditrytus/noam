#pragma once

#include <map>
#include <functional>

#include "AstCallbacks.h"
#include "astCallbackVisitor.h"

namespace noam {

    class AstCallbacksVisitor : public AstVisitorBase, private AstCallbacks {

    public:
        AstCallbacksVisitor(AstCallbacks callbacks);

        void preVisit(const TokenNode &node) override;

        void visit(const TokenNode &node) override;

        void postVisit(const TokenNode &node) override;

        void preVisit(const RuleNode &node) override;

        void visit(const RuleNode &node) override;

        void postVisit(const RuleNode &node) override;

    private:
        template <typename Callbacks, typename Node>
        void callAll(const Callbacks& callbacks, const Node& node);

    };

}



