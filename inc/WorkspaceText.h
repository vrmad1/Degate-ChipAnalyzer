/* -*-c++-*-

  This file is part of the IC reverse engineering tool degate.

  Copyright 2008, 2009, 2010 by Martin Schobert

  Degate is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  any later version.

  Degate is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with degate. If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __WORKSPACETEXT_H__
#define __WORKSPACETEXT_H__

#include <QtOpenGL/QtOpenGL>

#define TEXT_SPACE 3
#define FONT_GLYPH_SIZE 32
#define FONT_ATLAS_SIZE 512.0
#define FONT_GLYPH_PER_LINE 16
#define FONT_DEFAULT_SIZE 20

namespace degate
{
	class WorkspaceText
	{
	public:
		/*
		 * Call this one time to init the font (that will be use for every text).
		 */
		static void init_font();

		/*
		 * Delete the font.
		 */
		static void delete_font();

		/*
		 * Call this to draw a single text (no vbo, less performance than normal use except if you need an update at each frame).
		 * 
		 * @param x : left bottom corner x coordinate of the first letter.
		 * @param y : left bottom corner y coordinate of the first letter.
		 * @param text : text to draw;
		 * @param projection : the projection matrix to apply. 
		 * @param size : size of the text, the texture atlas is Arial 20.
		 */
		static void draw_single(unsigned x, unsigned y, const char* text, const QMatrix4x4& projection, const unsigned size = FONT_DEFAULT_SIZE);

		WorkspaceText(QWidget* new_parent);
		~WorkspaceText();

		/*
		 * Init OpenGL routine (vbo).
		 */
		void init();

		/*
	     * Update all vbo with a new total size.
	     * 
	     * @param size : the size of total text to draw.
	     */
		void update(unsigned size);

		/*
	     * Add a new text to the vbo (that will be drawn with others).
	     * 
	     * @param offset : offset to the first character of the first string.
	     * @param x : left bottom corner x coordinate of the first letter.
		 * @param y : left bottom corner y coordinate of the first letter.
		 * @param text : text to draw;
		 * @param size : size of the text, the texture atlas is Arial 20.
	     */
		void add_sub_text(unsigned offset, unsigned x, unsigned y, const char* text, const unsigned size = FONT_DEFAULT_SIZE);

		/*
	     * Draw all text in the vbo.
	     * 
	     * @param projection : the projection matrix to apply. 
	     */
		void draw(const QMatrix4x4& projection);

	private:
		static GLuint font_texture;
		static QOpenGLShaderProgram program;
		static QOpenGLFunctions* context;

		QWidget* parent;
		GLuint vbo;
		unsigned total_size;

	};
}

#endif