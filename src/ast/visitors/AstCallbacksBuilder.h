#pragma once

#include <functional>

#include "noam-rules.h"

#include "AstCallbacks.h"


namespace noam {

    class SetRuleCallback;
    class SetTokenCallback;
    class SetTokenOrNewCallback;
    class SetRuleOrNewCallback;

    class NewCallback {

    public:
        virtual SetRuleCallback& For(const SimpleRule& rule) = 0;
        virtual SetTokenCallback& For(const Terminal& terminal) =0;
    };

    class SetTokenCallback {

    public:
        virtual SetTokenOrNewCallback& PreVisit(std::function<void(const TokenNode&)> callback) = 0;
        virtual SetTokenOrNewCallback& Visit(std::function<void(const TokenNode&)> callback) = 0;
        virtual SetTokenOrNewCallback& PostVisit(std::function<void(const TokenNode&)> callback) = 0;
    };

    class SetRuleCallback {
    public:
        virtual SetRuleOrNewCallback& PreVisit(std::function<void(const RuleNode&)> callback) = 0;
        virtual SetRuleOrNewCallback& Visit(std::function<void(const RuleNode&)> callback) = 0;
        virtual SetRuleOrNewCallback& PostVisit(std::function<void(const RuleNode&)> callback) = 0;
    };

    class SetTokenOrNewCallback : public virtual NewCallback, public SetTokenCallback {};

    class SetRuleOrNewCallback : public virtual NewCallback, public SetRuleCallback {};

    class AstCallbacksBuilder
            : SetTokenOrNewCallback
            , SetRuleOrNewCallback
            , public AstCallbacks {
    public:
        SetRuleCallback &For(const SimpleRule &rule) override;

        SetTokenCallback &For(const Terminal &terminal) override;

    private:
        SetTokenOrNewCallback &PreVisit(std::function<void(const TokenNode &)> callback) override;

        SetTokenOrNewCallback &Visit(std::function<void(const TokenNode &)> callback) override;

        SetTokenOrNewCallback &PostVisit(std::function<void(const TokenNode &)> callback) override;

        SetRuleOrNewCallback &PreVisit(std::function<void(const RuleNode &)> callback) override;

        SetRuleOrNewCallback &Visit(std::function<void(const RuleNode &)> callback) override;

        SetRuleOrNewCallback &PostVisit(std::function<void(const RuleNode &)> callback) override;

    private:
        std::shared_ptr<SimpleRule> currentRule;
        std::shared_ptr<Terminal> currentTerminal;

    };

}
