#ifndef CHESS_V2_INTERPOLATOR_H
#define CHESS_V2_INTERPOLATOR_H

#include <memory>

class Interpolator {
public:
    using Unique = std::unique_ptr<Interpolator>;
    using Shared = std::shared_ptr<Interpolator>;
    using Ref = std::reference_wrapper<Interpolator>;

    /**
     * \param progress value between 0.0 and 1.0 indicating progress of the animation (completion part)
     * \return interpolated value
     */
    virtual float Interpolate(float progress) = 0;

    virtual ~Interpolator() = default;
};

class LinearInterpolator : public Interpolator {
public:
    float Interpolate(float progress) override;
};

class AccelerateInterpolator : public Interpolator {
public:
    float Interpolate(float progress) override;
};


#endif //CHESS_V2_INTERPOLATOR_H
