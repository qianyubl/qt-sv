#ifndef GPU_RENDER_H
#define GPU_RENDER_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <vector>

#include <opencv2/opencv.hpp>

//#include "v4l2capture.h"
//#include "model.h"
//#include "cameraparameter.h"
//#include "camera3d.h"

//#include "nxp/ModelLoader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

QT_BEGIN_NAMESPACE
class QGestureEvent;
QT_END_NAMESPACE

using namespace std;
using namespace cv;

#define CAMERA_NUM  4
#define VAO_NUM 8 // 2 * CAMERA_NUM

extern "C"
{
#include <pthread.h>
}

class GpuRender : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
   explicit GpuRender(QWidget *parent = 0);
    ~GpuRender();

//    void allocate_buffer(uint num);
//    void setBuf(QVector<V4l2Capture::CapBuffers *> &pbuf);
//    void enablePaint();
//    void setCameraPara(QVector<CameraParameter> &p);

public slots:

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    bool event(QEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

#define PLANES 4

private:
//    typedef void (GL_APIENTRY *PFNGLTEXDIRECTVIVMAP)
//                 (GLenum Target, GLsizei Width, GLsizei Height,
//                  GLenum Format, GLvoid ** Logical, const GLuint *Physical);
//    typedef void (GL_APIENTRY *PFNGLTEXDIRECTINVALIDATEVIV) (GLenum Target);
//    PFNGLTEXDIRECTVIVMAP pFNglTexDirectVIVMap;
//    PFNGLTEXDIRECTINVALIDATEVIV pFNglTexDirectInvalidateVIV;

    QVector<QString> cameraNames;
//    QVector<Model*> objModels;
//    QVector<CameraParameter> *camParas;

    QSize textureSize;
    GLuint textureCam;
    GLint textureLoc;
    GLint extrinsicLoc;
    QOpenGLShaderProgram *m_program;
    GLuint indexTransformBlock;
    GLuint programId;
    GLuint idUbo;
    GLint blockSize;
    GLfloat *pblockBuf;

//    QVector<V4l2Capture::CapBuffers *> buffers;
//    std::vector<void *> pTexBuffers;

    pthread_mutex_t gpu_mutex;
    pthread_cond_t gpu_cond;

    bool paintFlag;

    unsigned char *alphaMasks[PLANES];
    GLuint maskTextureID[PLANES];
    GLint maskTextureLoc;

//    Camera3D *camera3D;

    //=============================== nxp sv
//    XMLParameters param;
    int camera_num;
    vector<int> g_in_width;				// Input frame width
    vector<int> g_in_height;			// Input frame height
    //Model Loader
    glm::mat4 gProjection;	// Initialization is needed
    float rx = 0.0f, ry = 0.0f, px = 0.0f, py = 0.0f, pz = -10.0f;
    glm::vec3 car_scale = glm::vec3(1.0f, 1.0f, 1.0f);
    QOpenGLShaderProgram renderProgram;
    QOpenGLShaderProgram exposureCorrectionProgram;
    QOpenGLShaderProgram renderProgramWB;
    QOpenGLShaderProgram carModelProgram;
    QOpenGLShaderProgram showTexProgram;
    GLuint mvpUniform, mvUniform, mnUniform;
    QVector<QOpenGLTexture *> textures;
//    vector<v4l2Camera> v4l2_cameras;	// Camera buffers
    GLuint VAO[VAO_NUM];
    vector<int> vertices;

    // Cameras mapping
    GLuint gTexObj[VAO_NUM] = {0};		// Camera textures
    GLuint txtMask[CAMERA_NUM] = {0};	// Camera masks textures
    vector<Mat> mask;					// Mask images

    QVector2D mousePressPos;

//    ModelLoader modelLoader;
//    MRT* mrt = NULL;	// Initialization is needed

//    Gains* gain = NULL;
//    int setParam(XMLParameters* xml_param);
    int programsInit();
    bool RenderInit();
    int camerasInit();
    void camTexInit();
    void vLoad(GLfloat** vert, int* num, string filename);
    void bufferObjectInit(GLuint* text_vao, GLuint* text_vbo, GLfloat* vert, int num);
    void texture2dInit(GLuint* textures);
    void ecTexInit();
    void mapFrame(int buf_index, int camera);
};

#endif // GPU_RENDER_H