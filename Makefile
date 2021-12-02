##
## Makefile for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio
##
## Made by guillaume wilmot
## Login   <wilmot_g@epitech.net>
##
## Started on  Sat May 14 18:16:27 2016 guillaume wilmot
## Last update Sun Jun  5 23:10:49 2016 guillaume wilmot
##

NAME	 	 = bomberman

SRC 		 = BombManager.cpp		\
		   CameraManager.cpp		\
		   ClassicBomb.cpp		\
		   CMeshCombiner.cpp		\
		   Displayer.cpp		\
		   FactoryPowerUps.cpp		\
		   FireManager.cpp		\
		   FpsCamera.cpp		\
		   Camera.cpp			\
		   Game.cpp			\
		   Lagrange.cpp			\
		   Map.cpp			\
		   MoreBomb.cpp			\
		   PathFinding.cpp		\
		   Player.cpp			\
		   Players.cpp			\
		   PowerUp.cpp			\
		   RangeDown.cpp		\
		   RangeUp.cpp			\
		   Sdl.cpp			\
		   Shield.cpp			\
		   SpeedDown.cpp		\
		   SpeedUp.cpp			\
		   StaticCamera.cpp		\
		   SuddenDeath.cpp		\
		   ThreadManager.cpp		\
		   Tile.cpp			\
		   main.cpp			\
		   DisplayHighScores.cpp 	\
		   DisplayNewGame.cpp		\
		   DisplayCredits.cpp 		\
		   DisplaySound.cpp 		\
		   Back.cpp			\
		   Binding.cpp			\
		   Credits.cpp			\
		   HighScores.cpp		\
		   Menu.cpp			\
		   Options.cpp			\
		   Play.cpp			\
		   Quit.cpp			\
		   DisplayBinding.cpp		\
		   Sound.cpp			\
		   Score.cpp			\
		   ListScores.cpp		\
		   Gui.cpp			\
		   IA.cpp

WHERE		 = /home/${USER}

OBJ		 = $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

OBJDIR		 = obj/

MAKEOBJ		 = obj

SRCDIR		 = src/

BINPATH		 = .

ifeq ($(CC), clang)
CXX = g++ -std=c++11 -g -pthread -pg -Wl,-rpath -Wl,./lib/Linux
else
CXX = g++ -std=c++11 -Wl,-rpath -Wl,./lib/Linux -pthread
endif

ifeq ($(CC), clang)
INS_CXX = g++ -std=c++11 -g -pthread -pg -Wl,-rpath -Wl,$(WHERE)/bomberman/lib
else
INS_CXX = g++ -std=c++11 -Wl,-rpath -Wl,$(WHERE)/bomberman/lib -pthread
endif

ifeq ($(GPROF), y)
CXX += -pg
endif


RM		 = rm -f

CXXFLAGS 	 =  -ffast-math

LDFLAGS 	 = -L./lib/$(SYSTEM) -lopencv_video -lopencv_highgui -lopencv_core -lavcodec -lswscale -lavformat -lavutil -lIrrlicht -lCEGUICoreWindowRendererSet -lCEGUIExpatParser -lCEGUIBase-0 -lCEGUIIrrlichtRenderer-0 -L/usr/X11R6/lib$(LIBSELECT)
LDFLAGS		 += -lGL -lXxf86vm -lX11 -ldl -lSDL -lSDL_mixer -lX11-xcb -lxcb

CPPFLAGS 	 = -I./includes -I./includes/irrlicht -I./includes/CEGUI -I/usr/X11R6/include $(USERCPPFLAGS) -I./includes/chaiscript -I./includes/SDL

DESTPATH 	 = $(BINPATH)/$(NAME)$(SUF)

SYSTEM	 	 = Linux

INS_LDFLAGS 	 = -L$(WHERE)/bomberman/lib -lopencv_video -lopencv_highgui -lopencv_core -lavcodec -lswscale -lavformat -lavutil -lIrrlicht -lCEGUICoreWindowRendererSet -lCEGUIExpatParser -lCEGUIBase-0 -lCEGUIIrrlichtRenderer-0 -L/usr/X11R6/lib$(LIBSELECT)

INS_LDFLAGS	 += -lGL -lXxf86vm -lX11 -ldl -lSDL -lSDL_mixer -lX11-xcb -lxcb

all:
	@make --no-print-directory $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(MAKEOBJ)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) -R $(OBJDIR)

re:	fclean all

install: $(OBJ)
	@mkdir -p $(WHERE)/bomberman/lib
	@cp ./lib/Linux/* $(WHERE)/bomberman/lib/
	@cp -r ./assets $(WHERE)/bomberman
	@cp -r ./ressources $(WHERE)/bomberman
	$(INS_CXX) $(OBJ) -o $(WHERE)/bomberman/$(NAME) $(INS_LDFLAGS)

.PHONY: all clean fclean re install
