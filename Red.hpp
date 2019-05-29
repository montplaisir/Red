
class Red
{
    private:

    public:
    Red()
    {};

    virtual ~Red() {};

    // This is the eval function that will be run in parallel.
    // In Cython, it will be a callback.
    virtual bool eval();

    bool run(bool &stop);
};

