#ifndef HFT_TIME_DAYCOUNT_HPP
#define HFT_TIME_DAYCOUNT_HPP
#include "date.hpp"

namespace hft::time {

    enum class DayCountConvention{
        ACT_360,
        ACT_365,
        ACT_365F,
        ACT_ACT,
        THIRTY_360,
        THIRTY_365,
        THIRTY_365F
    };

    class DayCountConventionBase{
        public:
        virtual ~DayCountConventionBase() = default;
        virtual double operator()(const Date& start, const Date& end) const = 0;
    };

    class DayCountConventionACT_360: public DayCountConventionBase{
        public:
        double operator()(const Date& start, const Date& end) const override;
    };


    class DayCountConventionACT_365F: public DayCountConventionBase{
        public:
        double operator()(const Date& start, const Date& end) const override;
    };

    class DayCountConventionACT_ACT: public DayCountConventionBase{
        public:
        double operator()(const Date& start, const Date& end) const override;
    };

    class DayCountConventionTHIRTY_360: public DayCountConventionBase{
        public:
        double operator()(const Date& start, const Date& end) const override;
    };

    class DayCountConventionTHIRTY_365: public DayCountConventionBase{
        public:
        double operator()(const Date& start, const Date& end) const override;
    };

    class DayCountConventionTHIRTY_ACT: public DayCountConventionBase{
        public:
        double operator()(const Date& start, const Date& end) const override;
    };
};

#endif //HFT_TIME_DAYCOUNT_HPP