#include"RenderCmd.h"

#include"../base/Director.h"

 


void  RenderCmd_Quad::exec(Texture2D *tex)
{

	GLuint id = tex->getTextureID();
	tex->getFileName().c_str();


	glLoadIdentity();// vetex can work once

	glBindTexture(GL_TEXTURE_2D, id);

	// able alpha blend for the texture who has alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//able opacity
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor4f(1.0f, 1.0f, 1.0f, _opacity);


	//start to render

	glBegin(GL_QUADS);

	glTexCoord2f(_coord2f[0], _coord2f[1]); glVertex2f(_vertex[0].x, _vertex[0].y);
	glTexCoord2f(_coord2f[2], _coord2f[3]); glVertex2f(_vertex[1].x, _vertex[1].y);
	glTexCoord2f(_coord2f[4], _coord2f[5]); glVertex2f(_vertex[2].x, _vertex[2].y);
	glTexCoord2f(_coord2f[6], _coord2f[7]); glVertex2f(_vertex[3].x, _vertex[3].y);



	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glEnd();
}
