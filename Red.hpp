
#ifndef __RED__
#define __RED__

// Evaluator
class Red
{
    private:

    public:
    Red()
    {};

    virtual ~Red() {};

    // This is the eval function that will be run in parallel.
    // In Cython, it will be a callback.
    virtual bool eval(const int i) const;
};

#endif // __RED__
