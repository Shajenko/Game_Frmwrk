#ifndef RENDERER_H
#define RENDERER_H


class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        virtual void submit();
        virtual void flush();
    protected:
    private:
};

#endif // RENDERER_H
