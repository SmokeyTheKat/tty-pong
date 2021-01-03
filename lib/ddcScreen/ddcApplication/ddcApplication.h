#ifndef __ddcApplications__
#define __ddcApplications__

#include "../../ddcDef/ddcDef.h"
#include "../../ddcVec/ddcVec.h"
#include "../ddcCursor/ddcCursor.h"
#include "../ddcShapes/ddcShapes.h"
#include "../../ddcCharSets/ddcCharSets.h"
#include "../../ddcPrint/ddcPrint.h"
#include "../../ddcString/ddcString.h"
#include "../../ddcGArray/ddcGArray.h"
#include "../../ddcKeyboard/ddcKeyboard.h"

struct ddApplication;
struct ddSelect;
struct ddPanel;
struct ddText;
struct ddEventSystem;


typedef struct ddApplication ddApplication;
typedef struct ddSelect ddSelect;
typedef struct ddPanel ddPanel;
typedef struct ddText ddText;
typedef struct ddEventSystem ddEventSystem;

typedef enum ddaTextAlign ddaTextAlign;
typedef enum ddAppDrawingElems ddAppDrawingElems;
enum ddaTextAlign { ALIGN_LEFT=0, ALIGN_CENTER, ALIGN_RIGHT };
enum ddAppDrawingElems { DDAE_NONE=0, DDAE_GRAPHICSFUNCTION, DDAE_DDSELECT, DDAE_DDPANEL, DDAE_DDTEXT, DDAE_DDLINE };

ddApplication init_ddApplication(ddString _name, ddColor _fgc, ddColor _bgc);
void exit_ddApplication(ddApplication* _da);
void run_ddApplication(ddApplication* _da);
void loop_ddApplication(ddApplication* _da, void (*f)(ddApplication*));
void ddApplication_clear_selected(ddApplication* _da);
bool ddApplication_get_input(void);
void ddApplication_update_selected(ddApplication* _da);
void ddApplication_increment_element_selected(ddApplication* _da, int _dv);
void ddApplication_event_onClick(ddApplication* _da);

ddText make_ddText(ddString _text, ddVec2 _pos, ddColor _fgc, ddColor _bgc);
void raze_ddText(ddText* _dt);
void draw_ddText(ddText _dt);

ddPanel make_ddPanel(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc);
void raze_ddPanel(ddPanel* _dp);
void draw_ddPanel(ddPanel _dp);

ddSelect make_ddSelect(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc, ddsize _ds, ddColor _sbc);
void raze_ddSelect(ddSelect* _ds);
bool ddSelect_addOption(ddSelect* _ds, ddText _dt, void (*_func)(int));
void draw_ddSelect(ddSelect _ds);
void draw_ddSelect_selected(ddSelect _ds);
void clear_ddSelect_selected(ddSelect _ds);


struct ddEventSystem
{
	void (*onClick)(int);
	void (*onSpace)(int);
	void (*onSelect)(int);
};

struct ddApplication
{
	ddString name;
	DOStatus status;

	ddGArray drawStack;
	ddAppDrawingElems* drawStackElems;
	ddsize drawStackLength;

	int selected;

	ddColor BGColor;
	ddColor FGColor;
};

struct ddText
{
	ddVec2 position;
	ddString text;
	ddColor FGColor;
	ddColor BGColor;

	ddaTextAlign textAlign;
	bool selectable;

	DOStatus status;
};

struct ddPanel
{
	ddVec2 position;
	ddVec2 size;

	DOStatus status;

	ddSquare element;
	ddText title;
	bool selectable;

	ddColor BGColor;
	ddColor FGColor;
};

struct ddSelect
{
	ddPanel panel;

	void (**onClick)(int);
	ddText* options;
	ddsize optionsLength;
	ddsize optionsSize;
	int selected;
	bool selectable;

	ddColor selectedBGColor;

	DOStatus status;
};





ddApplication init_ddApplication(ddString _name, ddColor _fgc, ddColor _bgc)
{
	ddApplication _o;
	_o.name = _name;

	_o.drawStack = make_ddGArray(10);
	_o.drawStackElems = malloc(10* sizeof(ddAppDrawingElems));
	_o.drawStackElems[0] = 1;
	//_o.drawStackElems = make(ddAppDrawingElems, 10);
	_o.drawStackLength = 10;

	_o.selected = 0;

	_o.BGColor = _bgc;
	_o.FGColor = _fgc;

	_o.status = DOS_ACTIVE;

	return _o;
}
void exit_ddApplication(ddApplication* _da)
{
	raze_ddGArray(&(_da->drawStack));
	raze(_da->drawStackElems);
	raze_ddString(&(_da->name));
}
void run_ddApplication(ddApplication* _da)
{
	ddApplication_update_selected(_da);
	for(;;)
	{
		cursor_clear();
		for (int i = 0; i < _da->drawStack.length; i++)
		{
			switch (_da->drawStackElems[i])
			{
				case DDAE_DDSELECT:
				{
					draw_ddSelect(ddGArray_get(_da->drawStack, i, ddSelect));
					break;
				}
				case DDAE_DDPANEL:
				{
					draw_ddPanel(ddGArray_get(_da->drawStack, i, ddPanel));
					break;
				}
				case DDAE_DDTEXT:
				{
					draw_ddText(ddGArray_get(_da->drawStack, i, ddText));
					break;
				}
				case DDAE_DDLINE:
				{
					draw_thick_line(ddGArray_get(_da->drawStack, i, ddLine), cset_block);
					break;
				}
				case DDAE_GRAPHICSFUNCTION:
				{
					void(*_tfunct)(void) = __ddGArray_get(_da->drawStack, i);
					(*_tfunct)();
				}
			}
		}
		for(;;)
		{
			ddKeyInfo dk = ddKey_getch();
			if (dk == DDK_TAB)
			{
				ddApplication_clear_selected(_da);
				_da->selected++;
				ddApplication_update_selected(_da);
			}
			if (dk == DDK_LEFT)
			{
				ddApplication_clear_selected(_da);
				_da->selected--;
				ddApplication_update_selected(_da);
			}
			if (dk == DDK_RIGHT)
			{
				ddApplication_clear_selected(_da);
				_da->selected++;
				ddApplication_update_selected(_da);
			}
			if (dk == DDK_DOWN)
			{
				ddApplication_clear_selected(_da);
				ddApplication_increment_element_selected(_da, 1);
				ddApplication_update_selected(_da);
			}
			if (dk == DDK_UP)
			{
				ddApplication_clear_selected(_da);
				ddApplication_increment_element_selected(_da, -1);
				ddApplication_update_selected(_da);
			}
			if (dk == DDK_RETURN)
			{
				ddApplication_event_onClick(_da);
			}
		}
	}
}
void ddApplication_event_onClick(ddApplication* _da)
{
	switch (_da->drawStackElems[_da->selected])
	{
		case DDAE_DDSELECT:
		{
			ddSelect* _t = ddGArray_get_p(_da->drawStack, _da->selected, ddSelect);
			(*(_t->onClick[_t->selected]))(_t->selected);
			break;
		}
		case DDAE_DDPANEL:
		{
			break;
		}
		case DDAE_DDTEXT:
		{
			break;
		}
		case DDAE_DDLINE:
		{
			break;
		}
	}

}
void ddApplication_increment_element_selected(ddApplication* _da, int _dv)
{
	switch (_da->drawStackElems[_da->selected])
	{
		case DDAE_DDSELECT:
		{
			ddSelect* _t = ddGArray_get_p(_da->drawStack, _da->selected, ddSelect);
			if (_t->selectable)
			{
				_t->selected+=_dv;
			}
			break;
		}
		case DDAE_DDPANEL:
		{
			break;
		}
		case DDAE_DDTEXT:
		{
			break;
		}
		case DDAE_DDLINE:
		{
			break;
		}
	}
}
void ddApplication_clear_selected(ddApplication* _da)
{
	switch (_da->drawStackElems[_da->selected])
	{
		case DDAE_DDSELECT:
		{
			ddSelect _t = ddGArray_get(_da->drawStack, _da->selected, ddSelect);
			if (_t.selectable) clear_ddSelect_selected(_t);
			break;
		}
		case DDAE_DDPANEL:
		{
			break;
		}
		case DDAE_DDTEXT:
		{
			break;
		}
		case DDAE_DDLINE:
		{
			break;
		}
	}

}
void ddApplication_update_selected(ddApplication* _da)
{
	switch (_da->drawStackElems[_da->selected])
	{
		case DDAE_DDSELECT:
		{
			ddSelect _t = ddGArray_get(_da->drawStack, _da->selected, ddSelect);
			if (_t.selectable) draw_ddSelect_selected(_t);
			break;
		}
		case DDAE_DDPANEL:
		{
			break;
		}
		case DDAE_DDTEXT:
		{
			break;
		}
		case DDAE_DDLINE:
		{
			break;
		}
	}
}
bool ddApplication_get_input(void)
{
	ddKeyInfo dki = ddKey_getch();
	if (dki == DDK_UP || dki == DDK_DOWN || dki == DDK_LEFT || dki == DDK_RIGHT)
		return true;
	return false;
}
void loop_ddApplication(ddApplication* _da, void (*f)(ddApplication*))
{
	for(;;) 
	{
		cursor_clear();
		(*f)(_da);
	}
}










ddText make_ddText(ddString _text, ddVec2 _pos, ddColor _fgc, ddColor _bgc)
{
	ddText _o;
	_o.text       = _text;
	_o.position   = _pos;
	_o.FGColor    = _fgc;
	_o.BGColor    = _bgc;
	_o.textAlign  = ALIGN_LEFT;
	_o.status     = DOS_ACTIVE;
	return _o;
}
ddText make_dft_ddText(ddString _text)
{
	ddText _o;
	_o.text       = _text;
	_o.position   = make_ddVec2(0,0);
	_o.FGColor    = make_ddColor(-1,-1,-1);
	_o.BGColor    = make_ddColor(-1,-1,-1);
	_o.textAlign  = ALIGN_LEFT;
	_o.status     = DOS_ACTIVE;
	return _o;
}
void raze_ddText(ddText* _dt)
{
	if (_dt->status != DOS_DELETED)
		raze_ddString(&(_dt->text));
	_dt->status = DOS_DELETED;
}
void draw_ddText(ddText _dt)
{
	cursor_color_push();
	if (_dt.textAlign == ALIGN_LEFT)
	{
		cursor_set_fg_color(_dt.FGColor);
		cursor_set_bg_color(_dt.BGColor);
		cursor_move_to_vec(_dt.position);
		cursor_write_ddString(_dt.text);
	}
	cursor_color_pop();
}




ddPanel make_ddPanel(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc)
{
	ddPanel _o;
	_o.position = _pos;
	_o.size = _size;
	_o.title = _title;
	_o.BGColor = _bgc;
	_o.FGColor = make_ddColor(0,0,0);
	_o.element = make_ddSquare(_pos, _size, " ");
	_o.status = DOS_ACTIVE;
	return _o;
}
void raze_ddPanel(ddPanel* _ds)
{
	if (_ds->status != DOS_DELETED)
	{
		raze_ddText(&(_ds->title));
	}
	_ds->status = DOS_DELETED;
}
void draw_ddPanel(ddPanel _ds)
{
	cursor_color_push();
	cursor_set_fg_color(make_ddColor(0,0,0));
	cursor_set_bg_color(_ds.BGColor);
	draw_ddSquare(_ds.element);

	draw_thick_line_points(_ds.position, make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y), cset_horizontalBar);
	draw_thick_line_points(_ds.position, make_ddVec2(_ds.position.x, _ds.position.y+_ds.size.y-1), cset_verticalBar);
	draw_thick_line_points(make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1),
					make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y), cset_verticalBar);
	draw_thick_line_points(make_ddVec2(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1),
					make_ddVec2(_ds.position.x, _ds.position.y+_ds.size.y-1), cset_horizontalBar);

	cursor_move_to_vec(_ds.position);
	cursor_write_cstring(cset_upRightBar);

	cursor_move_to(_ds.position.x+_ds.size.x-1, _ds.position.y);
	cursor_write_cstring(cset_upLeftBar);

	cursor_move_to(_ds.position.x, _ds.position.y+_ds.size.y-1);
	cursor_write_cstring(cset_downRightBar);

	cursor_move_to(_ds.position.x+_ds.size.x-1, _ds.position.y+_ds.size.y-1);
	cursor_write_cstring(cset_downLeftBar);


	_ds.title.position = make_ddVec2((_ds.position.x+((int)(_ds.size.x/2)))-((int)(_ds.title.text.length/2)), (_ds.position.y));
	draw_ddText(_ds.title);

	cursor_move_to(((_ds.position.x+((int)(_ds.size.x/2)))-((int)(_ds.title.text.length/2)))-1, _ds.position.y);
	cursor_write_cstring(cset_rightStopBar);

	cursor_move_to(((_ds.position.x+((int)(_ds.size.x/2)))-((int)(_ds.title.text.length/2)))+_ds.title.text.length, _ds.position.y);
	cursor_write_cstring(cset_leftStopBar);


	cursor_color_pop();
}


ddSelect make_ddSelect(ddVec2 _pos, ddVec2 _size, ddText _title, ddColor _bgc, ddsize _ds, ddColor _sbc)
{
	ddSelect _o;
	_o.panel = make_ddPanel(_pos, _size, _title, _bgc);
	_o.optionsSize = _ds;
	_o.options = make(ddText, _ds);
	_o.onClick = calloc(_ds, sizeof(void (*)(int)) );
	_o.optionsLength = 0;
	_o.selected = 0;
	_o.selectable = false;
	_o.selectedBGColor = _sbc;
	_o.status = DOS_ACTIVE;
	return _o;
}
void raze_ddSelect(ddSelect* _ds)
{
	if (_ds->status != DOS_DELETED)
	{
		for (int i = 0; i < _ds->optionsLength; i++)
		{
			raze_ddText(&(_ds->options[i]));
		}
		raze(_ds->options);
		raze(_ds->onClick);
	}
	_ds->status = DOS_DELETED;
}
bool ddSelect_addOption(ddSelect* _ds, ddText _dt, void (*_func)(int))
{
	if (_ds->status == DOS_DELETED) return false;
	if (_ds->optionsLength+1 > _ds->optionsSize)
		return false; 

	_ds->selectable = true;
	
	_ds->options[_ds->optionsLength] = _dt;
	_ds->onClick[_ds->optionsLength] = _func;

	_ds->optionsLength++;
	return true;
}
void draw_ddSelect(ddSelect _ds)
{
	cursor_color_push();
	draw_ddPanel(_ds.panel);
	cursor_set_bg_color(_ds.panel.BGColor);
	cursor_set_fg_color(_ds.panel.FGColor);
	for (int i = 0; i < _ds.optionsLength; i++)
	{
		_ds.options[i].position.x = _ds.panel.position.x+1;
		_ds.options[i].position.y = _ds.panel.position.y+1+i;
		draw_ddText(_ds.options[i]);
	}
	cursor_color_pop();
}
void draw_ddSelect_selected(ddSelect _ds)
{
	//draw_ddSelect(_ds);
	ddColor _t = _ds.options[_ds.selected].BGColor;
	_ds.options[_ds.selected].BGColor = _ds.selectedBGColor;
	
	draw_ddText(_ds.options[_ds.selected]);
	_ds.options[_ds.selected].BGColor = _t;
}
void clear_ddSelect_selected(ddSelect _ds)
{
	cursor_color_push();
	//draw_ddSelect(_ds);
	cursor_set_bg_color(_ds.panel.BGColor);
	cursor_set_fg_color(_ds.panel.FGColor);
	draw_ddText(_ds.options[_ds.selected]);
	cursor_color_pop();
}





#endif
