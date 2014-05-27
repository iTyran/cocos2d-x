/****************************************************************************
Copyright 2011 Jeff Lamarche
Copyright 2012 Goffredo Marocchi
Copyright 2012 Ricardo Quesada
Copyright 2012 cocos2d-x.org
Copyright 2013-2014 Chukong Technologies Inc.
 
 
http://www.cocos2d-x.org
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCGLPROGRAM_H__
#define __CCGLPROGRAM_H__

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "CCGL.h"
#include "math/CCMath.h"
#include <unordered_map>

NS_CC_BEGIN

/**
 * @addtogroup shaders
 * @{
 */

struct _hashUniformEntry;
class GLProgram;

typedef void (*GLInfoFunction)(GLuint program, GLenum pname, GLint* params);
typedef void (*GLLogFunction) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);


struct VertexAttrib
{
    GLuint index;
    GLint size;
    GLenum type;
    std::string name;
};

struct Uniform
{
    GLint location;
    GLint size;
    GLenum type;
    std::string name;
};

/** GLProgram类
 实现一个glProgram
 
 
 @since v2.0.0
 */
class CC_DLL GLProgram : public Ref
{
    friend class GLProgramState;

public:
    enum
    {
        VERTEX_ATTRIB_POSITION,
        VERTEX_ATTRIB_COLOR,
        VERTEX_ATTRIB_TEX_COORD,
        VERTEX_ATTRIB_NORMAL,

        VERTEX_ATTRIB_MAX,

        // 向后兼容
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };
    
    enum
    {
        UNIFORM_P_MATRIX,
        UNIFORM_MV_MATRIX,
        UNIFORM_MVP_MATRIX,
        UNIFORM_TIME,
        UNIFORM_SIN_TIME,
        UNIFORM_COS_TIME,
        UNIFORM_RANDOM01,
        UNIFORM_SAMPLER0,
        UNIFORM_SAMPLER1,
        UNIFORM_SAMPLER2,
        UNIFORM_SAMPLER3,

        UNIFORM_MAX,
    };
    
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR;
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP;
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV;
    static const char* SHADER_NAME_POSITION_COLOR;
    static const char* SHADER_NAME_POSITION_COLOR_NO_MVP;
    static const char* SHADER_NAME_POSITION_TEXTURE;
    static const char* SHADER_NAME_POSITION_TEXTURE_U_COLOR;
    static const char* SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
    static const char* SHADER_NAME_POSITION_U_COLOR;
    static const char* SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;

    static const char* SHADER_NAME_LABEL_NORMAL;
    static const char* SHADER_NAME_LABEL_OUTLINE;

    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_NORMAL;
    static const char* SHADER_NAME_LABEL_DISTANCEFIELD_GLOW;
    
    
    // 制服(uniform)名
    static const char* UNIFORM_NAME_P_MATRIX;
    static const char* UNIFORM_NAME_MV_MATRIX;
    static const char* UNIFORM_NAME_MVP_MATRIX;
    static const char* UNIFORM_NAME_TIME;
    static const char* UNIFORM_NAME_SIN_TIME;
    static const char* UNIFORM_NAME_COS_TIME;
    static const char* UNIFORM_NAME_RANDOM01;
    static const char* UNIFORM_NAME_SAMPLER0;
    static const char* UNIFORM_NAME_SAMPLER1;
    static const char* UNIFORM_NAME_SAMPLER2;
    static const char* UNIFORM_NAME_SAMPLER3;
    static const char* UNIFORM_NAME_ALPHA_TEST_VALUE;
    
    // 属性名
    static const char* ATTRIBUTE_NAME_COLOR;
    static const char* ATTRIBUTE_NAME_POSITION;
    static const char* ATTRIBUTE_NAME_TEX_COORD;
    static const char* ATTRIBUTE_NAME_NORMAL;

    GLProgram();
    virtual ~GLProgram();
    /** 使用顶点(vertex)和片段字节数组初始化GLProgram
     * @js initWithString
     * @lua initWithString
     */

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    /** 使用预编译着色器编程初始化CCGLProgram */
    static GLProgram* createWithPrecompiledProgramByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    bool initWithPrecompiledProgramByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
#endif

    /**  使用顶点(vertex)和字节数组片段初始化GLProgram
     * @js initWithString
     * @lua initWithString
     */
    static GLProgram* createWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);
    bool initWithByteArrays(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);

    /**  使用顶点(vertex)和文件名的内容片段初始化GLProgram
     * @js init
     * @lua init
     */
    static GLProgram* createWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);
    bool initWithFilenames(const std::string& vShaderFilename, const std::string& fShaderFilename);

	//void bindUniform(std::string uniformName, int value);
	Uniform* getUniform(const std::string& name);
    VertexAttrib* getVertexAttrib(const std::string& name);

    /**  通过调用glBindAttribLocation方法添加新的属性到着色器(shader) */
    void bindAttribLocation(const std::string& attributeName, GLuint index) const;

    /** 调用 glGetAttribLocation方法 */
    GLint getAttribLocation(const std::string& attributeName) const;

    /** 调用 glGetUniformLocation()方法 */
    GLint getUniformLocation(const std::string& attributeName) const;

    /** 链接 glProgram */
    bool link();
    /** 它将调用glUseProgram()方法 */
    void use();
/** 它将创建4种制式(uniforms):
    - kUniformPMatrix
    - kUniformMVMatrix
    - kUniformMVPMatrix
    - GLProgram::UNIFORM_SAMPLER

 且会绑定"GLProgram::UNIFORM_SAMPLER" 到0

 */
    void updateUniforms();
    
    /** 调用(retrieves)检索此着色器编程的指定名字制式的位置. */
    GLint getUniformLocationForName(const char* name) const;
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform1i.
     * @js setUniformLocationI32
     * @lua setUniformLocationI32
     */
    void setUniformLocationWith1i(GLint location, GLint i1);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform2i. */
    void setUniformLocationWith2i(GLint location, GLint i1, GLint i2);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform3i. */
    void setUniformLocationWith3i(GLint location, GLint i1, GLint i2, GLint i3);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform4i,仅仅当该值不同于前一个,相同的着色器(shader)编程才调. */
    void setUniformLocationWith4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform2iv. */
    void setUniformLocationWith2iv(GLint location, GLint* ints, unsigned int numberOfArrays);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform3iv. */
    void setUniformLocationWith3iv(GLint location, GLint* ints, unsigned int numberOfArrays);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform4iv. */
    
    void setUniformLocationWith4iv(GLint location, GLint* ints, unsigned int numberOfArrays);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform1f .
     * 在 js 或 lua中, 请使用 setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith1f(GLint location, GLfloat f1);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform2f .
     * 在 js 或 lua中, 请使用setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith2f(GLint location, GLfloat f1, GLfloat f2);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform3f.
     *在 js 或 lua中, 请使用 setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform4f.
     * I在 js 或 lua中, 请使用setUniformLocationF32
     * @js NA
     */
    void setUniformLocationWith4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform2fv. */
    void setUniformLocationWith2fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform3fv. */
    void setUniformLocationWith3fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniform4fv. */
    void setUniformLocationWith4fv(GLint location, const GLfloat* floats, unsigned int numberOfArrays);

    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniformMatrix2fv. */
    void setUniformLocationWithMatrix2fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniformMatrix3fv. */
    void setUniformLocationWithMatrix3fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** 仅当该值不同于前一个调用相同的着色器(shader)编程,调用 glUniformMatrix4fv. */
    void setUniformLocationWithMatrix4fv(GLint location, const GLfloat* matrixArray, unsigned int numberOfMatrices);
    
    /** 如果他们不同于前一个调用相同的着色器(shader),将会更新内键的制式. */
    void setUniformsForBuiltins();
    void setUniformsForBuiltins(const Mat4 &modelView);

    // Attribute

    /** 返回vertexShader错误记录 */
    std::string getVertexShaderLog() const;

    /** 返回fragmentShader错误记录 */
    std::string getFragmentShaderLog() const;

    /** 返回编程错误记录 */
    std::string getProgramLog() const;
    
    // 重加载所有的着色器（shaders）, 该方法转为android设计
    // 当 opengl 内容丢失,不调用它.
    void reset();
    
    inline const GLuint getProgram() const { return _program; }

    // DEPRECATED
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderByteArray(const GLchar* vertexByteArray, const GLchar* fragByteArray)
    { return initWithByteArrays(vertexByteArray, fragByteArray); }
    CC_DEPRECATED_ATTRIBUTE bool initWithVertexShaderFilename(const std::string &vertexFilename, const std::string& fragFilename)
    { return initWithFilenames(vertexFilename, fragFilename); }
    CC_DEPRECATED_ATTRIBUTE void addAttribute(const std::string &attributeName, GLuint index) const { return bindAttribLocation(attributeName, index); }


protected:
    bool updateUniformLocation(GLint location, const GLvoid* data, unsigned int bytes);
    virtual std::string getDescription() const;

    void bindPredefinedVertexAttribs();
    void parseVertexAttribs();
    void parseUniforms();

    bool compileShader(GLuint * shader, GLenum type, const GLchar* source);
    std::string logForOpenGLObject(GLuint object, GLInfoFunction infoFunc, GLLogFunction logFunc) const;

    GLuint            _program;
    GLuint            _vertShader;
    GLuint            _fragShader;
    GLint             _builtInUniforms[UNIFORM_MAX];
    struct _hashUniformEntry* _hashForUniforms;
	bool              _hasShaderCompiler;
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    std::string       _shaderId;
#endif

    struct flag_struct {
        unsigned int usesTime:1;
        unsigned int usesMVP:1;
        unsigned int usesMV:1;
        unsigned int usesP:1;
		unsigned int usesRandom:1;

        // handy way to initialize the bitfield
        flag_struct() { memset(this, 0, sizeof(*this)); }
    } _flags;

    std::unordered_map<std::string, Uniform> _userUniforms;
    std::unordered_map<std::string, VertexAttrib> _vertexAttribs;
};

NS_CC_END

#endif /* __CCGLPROGRAM_H__ */
