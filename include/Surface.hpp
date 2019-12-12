#include "Texture.h"
namespace bogong {
	class Surface {
		friend class Texture;
	protected:
		GLenum internal_format;
		GLenum target_type;

	public:
		Surface() {

		}

	};
}