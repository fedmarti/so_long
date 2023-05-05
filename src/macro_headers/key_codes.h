/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_codes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:22:10 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/05 15:28:06 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_CODES_H
# define KEY_CODES_H

# ifndef SPACE_KEY
#  define SPACE_KEY 32
# endif

// '
# ifndef SINGLE_APEX_KEY
#  define SINGLE_APEX_KEY 39 
# endif

// '
# ifndef APOSTROPHE_KEY
#  define APOSTROPHE_KEY SINGLE_APEX_KEY 
# endif

//,
# ifndef COMMA_KEY
#  define COMMA_KEY 44
# endif

//-
# ifndef DASH_KEY
#  define DASH_KEY 45
# endif

//.
# ifndef DOT_KEY
#  define DOT_KEY 46
# endif

// /
# ifndef SLASH_KEY
#  define SLASH_KEY 47
# endif

# ifndef ZERO_KEY
#  define ZERO_KEY 48
# endif

# ifndef ONE_KEY
#  define ONE_KEY 49
# endif

# ifndef TWO_KEY
#  define TWO_KEY 50
# endif

# ifndef THREE_KEY
#  define THREE_KEY 51
# endif

# ifndef FOUR_KEY
#  define FOUR_KEY 52
# endif

# ifndef FIVE_KEY
#  define FIVE_KEY 53
# endif

# ifndef SIX_KEY
#  define SIX_KEY 54
# endif

# ifndef SEVEN_KEY
#  define SEVEN_KEY 55
# endif

# ifndef EIGHT_KEY
#  define EIGHT_KEY 56
# endif

# ifndef NINE_KEY
#  define NINE_KEY 57
# endif

// ;
# ifndef SEMICOLON_KEY
#  define SEMICOLON_KEY 59 
# endif

// =
# ifndef EQUALS_KEY
#  define EQUALS_KEY 61
# endif

// [
# ifndef OPEN_SQUARE_BRACKET_KEY
#  define OPEN_SQUARE_BRACKET_KEY 91
# endif

/*   \                       */
# ifndef BACKSLASH_KEY
#  define BACKSLASH_KEY 92
# endif

// ]
# ifndef CLOSED_SQUARE_BRACKET_KEY
#  define CLOSED_SQUARE_BRACKET_KEY 93
# endif

// `
# ifndef BACKTICK_KEY
#  define BACKTICK_KEY 96
# endif

// `
# ifndef GRAVE_KEY
#  define GRAVE_KEY BACKTICK_KEY
# endif

# ifndef A_KEY
#  define A_KEY 97
# endif

# ifndef B_KEY
#  define B_KEY 98
# endif

# ifndef C_KEY
#  define C_KEY 99
# endif

# ifndef D_KEY
#  define D_KEY 100
# endif

# ifndef E_KEY
#  define E_KEY 101
# endif

# ifndef F_KEY
#  define F_KEY 102
# endif

# ifndef G_KEY
#  define G_KEY 103
# endif

# ifndef H_KEY
#  define H_KEY 104
# endif

# ifndef I_KEY
#  define I_KEY 105
# endif

# ifndef J_KEY
#  define J_KEY 106
# endif

# ifndef K_KEY
#  define K_KEY 107
# endif

# ifndef L_KEY
#  define L_KEY 108
# endif

# ifndef M_KEY
#  define M_KEY 109
# endif

# ifndef N_KEY
#  define N_KEY 110
# endif

# ifndef O_KEY
#  define O_KEY 111
# endif

# ifndef P_KEY
#  define P_KEY 112
# endif

# ifndef Q_KEY
#  define Q_KEY 113
# endif

# ifndef R_KEY
#  define R_KEY 114
# endif

# ifndef S_KEY
#  define S_KEY 115
# endif

# ifndef T_KEY
#  define T_KEY 116
# endif

# ifndef U_KEY
#  define U_KEY 117
# endif

# ifndef V_KEY
#  define V_KEY 118
# endif

# ifndef W_KEY
#  define W_KEY 119
# endif

# ifndef X_KEY
#  define X_KEY 120
# endif

# ifndef Y_KEY
#  define Y_KEY 121
# endif

# ifndef Z_KEY
#  define Z_KEY 122
# endif

# ifndef ENTER_KEY
#  define ENTER_KEY 65293
# endif

# ifndef BACKSPACE_KEY
#  define BACKSPACE_KEY 65228
# endif

# ifndef TAB_KEY
#  define TAB_KEY 65290
# endif

# ifndef ESC_KEY
#  define ESC_KEY	65307
# endif

# ifndef HOME_KEY
#  define HOME_KEY 65360
# endif

# ifndef ARROW_LEFT_KEY
#  define ARROW_LEFT_KEY 65361
# endif

# ifndef ARROW_UP_KEY
#  define ARROW_UP_KEY 65362
# endif

# ifndef ARROW_RIGHT_KEY
#  define ARROW_RIGHT_KEY 65363
# endif

# ifndef ARROW_DOWN_KEY
#  define ARROW_DOWN_KEY	65364
# endif

# ifndef PAGE_UP_KEY
#  define PAGE_UP_KEY 65365
# endif

# ifndef PAGE_DOWN_KEY
#  define PAGE_DOWN_KEY 65366
# endif

# ifndef INSERT_KEY
#  define INSERT_KEY 65379
# endif

//IDK WHAT TO SAY ABOUT THIS
//My keyboard doesn't even have this one
//on the school's keyboard it's sandwiched between right_ctrl
//and right fn
# ifndef MENU_KEY
#  define MENU_KEY 65383
# endif

# ifndef NUM_LOCK_KEY
#  define NUM_LOCK_KEY 65407
# endif

# ifndef NUMPAD_ENTER_KEY
#  define NUMPAD_ENTER_KEY 65421
# endif

# ifndef NUMPAD_SEVEN_KEY
#  define NUMPAD_SEVEN_KEY 65429
# endif

# ifndef NUMPAD_FOUR_KEY
#  define NUMPAD_FOUR_KEY 65430
# endif

# ifndef NUMPAD_EIGHT_KEY
#  define NUMPAD_EIGHT_KEY 65431
# endif

# ifndef NUMPAD_SIX_KEY
#  define NUMPAD_SIX_KEY 65432
# endif

# ifndef NUMPAD_TWO_KEY
#  define NUMPAD_TWO_KEY 65433
# endif

# ifndef NUMPAD_NINE_KEY
#  define NUMPAD_NINE_KEY 65434
# endif

# ifndef NUMPAD_THREE_KEY
#  define NUMPAD_THREE_KEY 65435
# endif

# ifndef NUMPAD_ONE_KEY
#  define NUMPAD_ONE_KEY 65436
# endif

# ifndef NUMPAD_FIVE_KEY
#  define NUMPAD_FIVE_KEY 65437
# endif

# ifndef NUMPAD_ZERO_KEY
#  define NUMPAD_ZERO_KEY 65438
# endif

# ifndef NUMPAD_DELETE_KEY
#  define NUMPAD_DELETE_KEY 65439
# endif

// +
# ifndef NUMPAD_PLUS_KEY
#  define NUMPAD_PLUS_KEY 65451
# endif

// *
# ifndef NUMPAD_ASTERISK_KEY
#  define NUMPAD_ASTERISK_KEY 65450
# endif

// -
# ifndef NUMPAD_DASH_KEY
#  define NUMPAD_DASH_KEY 65453
# endif

// /
# ifndef NUMPAD_SLASH_KEY
#  define NUMPAD_SLASH_KEY 65455
# endif

# ifndef F1_KEY
#  define F1_KEY 65470
# endif

# ifndef F2_KEY
#  define F2_KEY 65471
# endif

# ifndef F3_KEY
#  define F3_KEY 65472
# endif

# ifndef F4_KEY
#  define F4_KEY 65473
# endif

# ifndef F5_KEY
#  define F5_KEY 65474
# endif

# ifndef F6_KEY
#  define F6_KEY 65475
# endif

# ifndef F7_KEY
#  define F7_KEY 65476
# endif

# ifndef F8_KEY
#  define F8_KEY 65477
# endif

# ifndef F9_KEY
#  define F9_KEY 65478
# endif

# ifndef F10_KEY
#  define F10_KEY 65479
# endif

# ifndef F11_KEY
#  define F11_KEY 65480
# endif

# ifndef F12_KEY
#  define F12_KEY 65481
# endif

# ifndef SHIFT_LEFT_KEY
#  define SHIFT_LEFT_KEY 65505
# endif

# ifndef SHIFT_RIGHT_KEY
#  define SHIFT_RIGHT_KEY 65506
# endif

# ifndef CTRL_LEFT_KEY
#  define CTRL_LEFT_KEY 65507
# endif

# ifndef CTRL_RIGHT_KEY
#  define CTRL_RIGHT_KEY 65508
# endif

# ifndef CAPS_LOCK_KEY
#  define CAPS_LOCK_KEY 65509
# endif

# ifndef ALT_KEY
#  define ALT_KEY 65513
# endif

# ifndef ALT_GR_KEY
#  define ALT_GR_KEY 65514
# endif

# ifndef DELETE_KEY
#  define DELETE_KEY 65535
# endif

#endif