%!
% Copyright (C) 2001 Taiji Yamada and gs-cjk project
%
% This file is part of GNU Ghostscript.
% 
% GNU Ghostscript is distributed in the hope that it will be useful, but
% WITHOUT ANY WARRANTY.  No author or distributor accepts responsibility
% to anyone for the consequences of using it or for whether it serves any
% particular purpose or works at all, unless he says so in writing. Refer
% to the GNU General Public License for full details.
% 
% Everyone is granted permission to copy, modify and redistribute GNU
% Ghostscript, but only under the conditions described in the GNU General
% Public License.  A copy of this license is supposed to have been given
% to you along with GNU Ghostscript so you can know your rights and
% responsibilities.  It should be in a file named COPYING.  Among other
% things, the copyright notice and this notice must be preserved on all
% copies.

% $Id: CIDFnmap.sj,v 1.1 2004/01/14 16:59:46 atai Exp $
% CID fontmap for japanese-shift-jis encoding CIDFontName

(�l�r����)				/MS-Mincho	;
/#82l#82r#96#BE#92#A9			/MS-Mincho	;
(�l�r�o����)				/MS-PMincho	;
/#82l#82r#82o#96#BE#92#A9		/MS-PMincho	;
(�l�r ����)				/MS-Mincho	;
/#82l#82r#20#96#BE#92#A9		/MS-Mincho	;
(�l�r �o����)				/MS-PMincho	;
/#82l#82r#20#82o#96#BE#92#A9		/MS-PMincho	;

(@�l�r����)				/MS-Mincho	;
/@#82l#82r#96#BE#92#A9			/MS-Mincho	;
(@�l�r�o����)				/MS-PMincho	;
/@#82l#82r#82o#96#BE#92#A9		/MS-PMincho	;
(@�l�r ����)				/MS-Mincho	;
/@#82l#82r#20#96#BE#92#A9		/MS-Mincho	;
(@�l�r �o����)				/MS-PMincho	;
/@#82l#82r#20#82o#96#BE#92#A9		/MS-PMincho	;

(�l�r�S�V�b�N)				/MS-Gothic	;
/#82l#82r#83S#83V#83b#83N		/MS-Gothic	;
(�l�r�o�S�V�b�N)			/MS-PGothic	;
/#82l#82r#82o#83S#83V#83b#83N		/MS-PGothic	;
(�l�r �S�V�b�N)				/MS-Gothic	;
/#82l#82r#20#83S#83V#83b#83N		/MS-Gothic	;
(�l�r �o�S�V�b�N)			/MS-PGothic	;
/#82l#82r#20#82o#83S#83V#83b#83N	/MS-PGothic	;

(@�l�r�S�V�b�N)				/MS-Gothic	;
/@#82l#82r#83S#83V#83b#83N		/MS-Gothic	;
(@�l�r�o�S�V�b�N)			/MS-PGothic	;
/@#82l#82r#82o#83S#83V#83b#83N		/MS-PGothic	;
(@�l�r �S�V�b�N)			/MS-Gothic	;
/@#82l#82r#20#83S#83V#83b#83N		/MS-Gothic	;
(@�l�r �o�S�V�b�N)			/MS-PGothic	;
/@#82l#82r#20#82o#83S#83V#83b#83N	/MS-PGothic	;

(�������� W3)		/HeiseiMin-W3		;
(��������W3)		/HeiseiMin-W3		;
(�����p�S�V�b�N W5)	/HeiseiKakuGo-W5	;
(�����p�S�V�b�NW5)	/HeiseiKakuGo-W5	;
(���˖��� R)		/KozMin-Regular		;
(���˖���R)		/KozMin-Regular		;

%
% If you found an error at substituting /Adobe-Identity for a fontname
% in reading a PDF file, and if you are the owner of the actual font
% named as the fontname then you can use such locale-specific fonts by
% adding entry as follows:
%
% But, recent PDF files do not require /Adobe-Identity, locale-specific
% fonts. Thus, you may get worse for adding such entry.
%
%(HG�ۺ޼��M-PRO)	(hgrsmp.ttf)	/Identity	;
%(HG��������-PRO)	(hgrskp.ttf)	/Identity	;
%
% As another choise, following one line acts "a fallback font" for such
% as locale-specific fonts:
%
%/Adobe-Identity	(hgrskp.ttf)	/Identity	;
