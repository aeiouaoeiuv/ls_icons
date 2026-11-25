#ifndef LS_ICONS_H
# define LS_ICONS_H

# include <stdio.h>
# include <stdlib.h>

enum ls_icon_kind {
  LS_ICON_FILE,
  LS_ICON_EXEC,
  LS_ICON_DIR,
  LS_ICON_LINK,
  LS_ICON_LINK_DIR,
  LS_ICON_LINK_BROKEN,
  LS_ICON_FIFO,
  LS_ICON_SOCK,
  LS_ICON_CHARDEV,
  LS_ICON_BLOCKDEV
};

int print_icon(const char *filename, const size_t len, FILE *stream,
	       enum ls_icon_kind kind, int is_quoted, int is_colored);
int print_arrow_right(FILE *stream);

#endif /* LS_ICONS_H */
