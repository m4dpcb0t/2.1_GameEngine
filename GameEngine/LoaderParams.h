#ifndef LOADERPARAMS_H
#define LOADERPARAMS_H


 /*
    LoaderParams is simply a class that takes values
    into its constructor and sets them as member
    variables that can then be accessed to set the
    initial values of an object.
 */

class LoaderParams
{
    public:
       LoaderParams(float x, float y, float width, float height,
        int currentRow, char* fileName,char* fileID, int animSpeed = 0, int callbackID = 0)
       : m_x(x), m_y(y), m_width(width), m_height(height),
       m_currentRow(currentRow), m_fileName(fileName), m_fileID(fileID), m_animSpeed(animSpeed), m_callbackID(callbackID)
        { }

        float getX() const { return m_x; }
        float getY() const { return m_y; }
        float getWidth() const { return m_width; }
        float getHeight() const { return m_height; }
        int getNumFrames() const { return m_numFrames; }
        int getCurrentRow() const {return m_currentRow; }
        int getAnimSpeed() const { return m_animSpeed; }
        int getCallbackID() const { return m_callbackID; }
        char* getFileName() const { return m_fileName; }
        char* getFileID() const { return m_fileID; }

    private:

        char* m_fileName;
        char* m_fileID;

        float m_x;
        float m_y;
        float m_width;
        float m_height;
        int m_numFrames;
        int m_currentRow;
        int m_animSpeed;
        int m_callbackID;

};

#endif // LOADERPARAMS_H
