#include "Programs/TTT.hpp"
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <stdio.h>

/* max and min players */
static TTT::Value Max_Player;
static TTT::Value Min_Player;

int Max_Player_Color;
int Min_Player_Color;

double TTT::EvalState(const State s) const
{
    //add your implementation
    int i,j,k;
	int temp = m_nrToWin;
    int count;                  /* number of consecutive squares with same values */
    int chances_1[9999];		/* number of possible ways of success for FIRST player */
    int chances_2[9999];		/* number of possible ways of success for SECOND player */
    bool is_not_possible;       /* if route not possible */
    bool place_flag;            /* represents if non-zero value square is found in the iteration */
    TTT::Value flag;            /* holds the value of (i,j) square,1st square of possible route */
    TTT::Value val;             /* holds the value of new square in the possible route */
    double value_1 = 0;
    double value_2 = 0;

    memset( chances_1, 0, (m_nrToWin+1)*sizeof(int) );
    memset( chances_2, 0, (m_nrToWin+1)*sizeof(int) );

    /* check rows */
    /* for each square check possible number of rows of success and failures */
    for(i=0;i<m_nrRows;i++)
    {
      for(j=0;j<m_nrCols;j++)
      {
	/* check if a row of desired length exists from given square */
	if((m_nrCols-j)>=m_nrToWin)
	{
	  count = 0;
	  is_not_possible=0;
	  flag = GetValueState(s,i,j);
	  if(flag == TTT::EMPTY)
	    place_flag = 0;
	  else
	    place_flag = 1;
	  for(k=0;k<m_nrToWin;k++)
	  {
	    val=GetValueState(s,i,j+k);
	    if(val != TTT::EMPTY && val != flag && place_flag == 1)
	    {
	      is_not_possible=1;
	      break;
	    }
	    else if(val != TTT::EMPTY && place_flag == 0){
	      flag = val;
	      place_flag = 1;
	      count++;
	    }
	    else if(val != TTT::EMPTY && place_flag == 1){
	    	count++;
	    }

	  }
	  /* possible row */
	  if(!is_not_possible){
	    /* if all the boxes in row has zero */
	    if(count == 0)
	    {
	      chances_1[0]++;
	      chances_2[0]++;
	    } 
	    /* otherwise */
	    else
	    {
	    	flag==TTT::FIRST? chances_1[count]++ : chances_2[count]++;
	    }

	  }
		
	}
      }
    }

    /* Columns */
    /* for each square check possible number of columns of success and failures */
    for(i=0;i<m_nrRows;i++)
    {
      for(j=0;j<m_nrCols;j++)
      {
	/* check if a column of desired length exists from given square */
	if((m_nrRows-i) >= m_nrToWin)
	{
	  count = 0;
     	  is_not_possible=0;
	  flag = GetValueState(s,i,j);
	  if(flag == TTT::EMPTY)
 	    place_flag = 0;
	  else
	    place_flag = 1;
	  for(k=0;k<m_nrToWin;k++)
	  {
	    val=GetValueState(s,i+k,j);
	    if(val != TTT::EMPTY && val != flag && place_flag == 1)
	    {
	      is_not_possible=1;
	      break;
	    }
	    else if(val != TTT::EMPTY && place_flag == 0){
	    	flag = val;
		place_flag = 1;
		count++;
	    }
	    else if(val != TTT::EMPTY && place_flag == 1){
	      count++;
	    }

	  }
	  /* possible columns */
	  if(!is_not_possible){
	    /* if all the boxes in row has zero */
	    if(count == 0)
	    {
	      chances_1[0]++;
	      chances_2[0]++;
	    }
	    /* otherwise */
	    else
	    {
	      flag==TTT::FIRST? chances_1[count]++ : chances_2[count]++;
	    }
	  }
	}
      }
    }

    /* Diagonals */
    /* for each square check possible number of diagonals of success and failures */
    for(i=0;i<m_nrRows;i++)
    {
      for(j=0;j<m_nrCols;j++)
      {
	/* check if a diagonal of desired length exists from given square */
	if((m_nrCols-j)>=m_nrToWin && (m_nrRows-i) >= m_nrToWin)
	{
	  count = 0;
	  is_not_possible=0;
	  flag = GetValueState(s,i,j);
	  if(flag == TTT::EMPTY)
	    place_flag = 0;
	  else
	    place_flag = 1;
	  for(k=0;k<m_nrToWin;k++)
	  {
	    val=GetValueState(s,i+k,j+k);
	    if(val != TTT::EMPTY && val != flag && place_flag == 1)
	    {
	      is_not_possible=1;
	      break;
	    }
	    else if(val != TTT::EMPTY && place_flag == 0){
	      flag = val;
	      place_flag = 1;
	      count++;
	    }
	    else if(val != TTT::EMPTY && place_flag == 1){
	      count++;
	    }
	  }
	  /* possible diagonals */
	  if(!is_not_possible){
	    /* if all the boxes in row has zero */
	    if(count == 0)
	    {
	      chances_1[0]++;
	      chances_2[0]++;
	    }
	    /* otherwise */
	    else
	    {
	      flag==TTT::FIRST? chances_1[count]++ : chances_2[count]++;
	    }

	  }
	}
      }
    }

    /* Anti-diagonals */
    /* for each square check possible number of anti-diagonals of success and failures */
    for(i=0;i<m_nrRows;i++)
    {
      for(j=0;j<m_nrCols;j++)
      {
	/* check if a anti-diagonal of desired length exists from the given square */
	if((m_nrCols-j)>=m_nrToWin &&  i >= m_nrToWin-1)
	{
	  count = 0;
	  is_not_possible=0;
	  flag = GetValueState(s,i,j);
	  if(flag == TTT::EMPTY)
	    place_flag = 0;
	  else
	    place_flag = 1;
	  for(k=0;k<m_nrToWin;k++)
	  {
	    val=GetValueState(s,i-k,j+k);
	    if(val != TTT::EMPTY && val != flag && place_flag == 1)
	    {
	      is_not_possible=1;
	      break;
	    }
	    else if(val != TTT::EMPTY && place_flag == 0){
	      flag = val;
	      place_flag = 1;
	      count++;
	    }
	    else if(val != TTT::EMPTY && place_flag == 1){
	      count++;
	    }
	  }
	  /* possible anti-diagonals */
	  if(!is_not_possible){
	    /* if all the boxes in row has zero */
	    if(count == 0)
	    {
	      chances_1[0]++;
	      chances_2[0]++;
	    }
	    /* otherwise */
	    else
	    {
	      flag==TTT::FIRST? chances_1[count]++ : chances_2[count]++;
	    }
	  }
	}
      }
    }

    /* print possible successes*/
   /* printf("Eval state no of possible rows,columns,diagonals and anti-diagonals \n");
    for(i=0;i<m_nrToWin+1;i++)
    {
      printf("%d x's row %d\n",i,chances_1[i]);
      printf("%d o's row %d\n",i,chances_2[i]);
    }*/

    /* total possibles ways for max and min */	
    for(i=0;i<m_nrToWin+1;i++)
    {
      value_1 +=(chances_1[i]*pow(10.0,i+1));
      value_2 +=(chances_2[i]*pow(10.0,i+1));

    }
    if(Max_Player == TTT::FIRST)
      return value_1-value_2;
    else
      return value_2-value_1;

}	


void TTT::BestMove(State   s, 
		   int     depth, 
		   int     remMoves, 
		   int     lastMove,
		   Value   player,
		   double *bestScore,
		   int    *bestMove) const
{
   int i,j;
   double max_value = -HUGE_VAL; /* holds highest possible state value */  
   double state_value;           /* holds value of each state */
   
   /* check if Best Move is for Player BLUE of RED? 
    * set max and min players and their values accordingly
    */
   if( player == TTT::FIRST)
   {
     Max_Player =  TTT::FIRST;
     Min_Player = TTT::SECOND;
   }
   else if( player == TTT::SECOND)
   {
     Max_Player = TTT::SECOND;
     Min_Player = TTT::FIRST;
   }
   if(Max_Player == TTT::FIRST)
   {
     Max_Player_Color = 1;
   }
   else if(Max_Player == TTT::SECOND)
   {
     Min_Player_Color = -1;
   }

   /* for each possible child
    * call NegaMax and get the state value
    * keep track of highest possible score
    * and best move
    */
   for(i=0; i<m_nrRows; i++)
   {
     for(j=0; j<m_nrCols; j++)
     {
       if(GetValueState(s,i,j) == 0)
       {
	 State temp = CopyState(s);
	 SetValueState(temp,i,j,player);
	 state_value = NegaMax(temp, depth-1, -HUGE_VAL, HUGE_VAL, remMoves-1, IdFromRowCol(i,j), Min_Player_Color);

	 if(max_value < state_value)
	 {
	   max_value = state_value;
	   *bestMove = IdFromRowCol(i,j);
	 }
       }
     }
   }
   *bestScore = max_value;
}



double TTT::NegaMax(State   s, 
		    int     depth, 
		    double  alpha, 
		    double  beta, 
		    int     remMoves, 
		    int     lastMove,
		    int     color) const
{
    //add your implementation
    int i,j,Max;
    int score=0;

    /* if depth is zero evaluate state*/
    if(depth == 0)
    {
      return EvalState(s);
    }
    else
    {
      /* Max code */
      /* find a child with max value */
      if(Max_Player_Color == color)
      {
	for(i=0; i<m_nrRows; i++)
	{
	  for(j=0; j<m_nrCols; j++)
	  {
	    if(GetValueState(s,i,j) == 0)
	    {
	      State temp = CopyState(s);
	      SetValueState(temp,i,j,Max_Player);
	      score = NegaMax(temp, depth-1, alpha, beta, remMoves-1, IdFromRowCol(i,j), Min_Player_Color);
	      if(score > alpha)
		alpha=score;
	      if(alpha >= beta)
		return alpha;
	    }
	  }
	}
	return alpha;
      }
      /* Min code */
      /* Find a child with min value */
      else
      {
	for(i=0; i<m_nrRows; i++)
	{
	  for(j=0; j<m_nrCols; j++)
	  {
	    if(GetValueState(s,i,j) == 0)
	    {
	      State temp = CopyState(s);
	      SetValueState(temp,i,j,Min_Player);
	      score = NegaMax(temp, depth-1, alpha, beta, remMoves-1, IdFromRowCol(i,j), Min_Player_Color);
	      if(score < beta)
		beta=score;                                            
	      if(alpha >= beta)
		return beta;      
	    }
	  }
	}
      }
      return beta;
    }

    
}

bool TTT::CheckWin(const State s, const int r, const int c) const
{
    const Value val  = GetValueState(s, r, c);
    int   cons = 0, end;
    
    //check row
    cons = 0; end = std::min(m_nrCols, c + m_nrToWin);
    for(int i = std::max(0, c - m_nrToWin); i < end; ++i)
	if(GetValueState(s, r, i) != val)
	    cons = 0;
	else if((++cons) >= m_nrToWin)
	    return true;
    
    //check column
    cons = 0; end = std::min(m_nrRows, r + m_nrToWin);
    for(int i = std::max(0, r - m_nrToWin); i < end; ++i)
	if(GetValueState(s, i, c) != val)
	    cons = 0;
	else if((++cons) >= m_nrToWin)
	    return true;
    
    //check diagonal
    cons = 0; end = 1 + std::min(m_nrToWin - 1, std::min(m_nrRows - r - 1, m_nrCols - c - 1));
    for(int i = std::max(-m_nrToWin + 1, std::max(-r, -c)); i < end; ++i)
	if(GetValueState(s, r + i, c + i) != val)
	    cons = 0;
	else if((++cons) >= m_nrToWin)
	    return true;
    
    //check anti-diagonal
    cons = 0; end = 1 + std::min(m_nrToWin - 1, std::min(r, m_nrCols - c - 1));
    for(int i = std::max(-m_nrToWin + 1, std::max(r - m_nrRows + 1, -c)); i < end; ++i)
    {
	if(GetValueState(s, r - i, c + i) != val)
	    cons = 0;
	else if((++cons) >= m_nrToWin)
	    return true;
    }
    
    
    return false;
    
    
}


