#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EasingFunctions.generated.h"

/**
 * All Functions copied from: https://easings.net/ 
 */
UCLASS()
class SPACESCAVENGER_API UEasingFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	/**
	 * @brief https://easings.net/#easeInSine
	 * @param Input 
	 * @return 
	 */
	static float EaseInSine(const float Input);

	/**
	 * @brief https://easings.net/#easeOutSine
	 * @param Input 
	 * @return 
	 */
	static float EaseOutSine(const float Input);

	/**
	 * @brief https://easings.net/#easeInOutSine
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutSine(const float Input);

	/**
	 * @brief https://easings.net/#easeInQuad
	 * @param Input 
	 * @return 
	 */
	static float EaseInQuad(const float Input);

	/**
	 * @brief https://easings.net/#easeOutQuad
	 * @param Input 
	 * @return 
	 */
	static float EaseOutQuad(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutQuad
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutQuad(const float Input);

	/**
	 * @brief https://easings.net/#easeInCubic 
	 * @param Input 
	 * @return 
	 */
	static float EaseInCubic(const float Input);

	/**
	 * @brief https://easings.net/#easeOutCubic  
	 * @param Input 
	 * @return 
	 */
	static float EaseOutCubic(const float Input);

	/**
	 * @brief https://easings.net/#easeInOutCubic 
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutCubic(const float Input);

	/**
	 * @brief https://easings.net/#easeInQuart 
	 * @param Input 
	 * @return 
	 */
	static float EaseInQuart(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutQuart 
	 * @param Input 
	 * @return 
	 */
	static float EaseOutQuart(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutQuart 
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutQuart(const float Input);

	/**
	 * @brief https://easings.net/#easeInQuint  
	 * @param Input 
	 * @return 
	 */
	static float EaseInQuint(const float Input);
	/**
	 * @brief https://easings.net/#easeOutQuint   
	 * @param Input 
	 * @return 
	 */
	static float EaseOutQuint(const float Input);
	/**
	 * @brief https://easings.net/#easeInOutQuint  
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutQuint(const float Input);

	/**
	 * @brief https://easings.net/#easeInExpo  
	 * @param Input 
	 * @return 
	 */
	static float EaseInExpo(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutExpo  
	 * @param Input 
	 * @return 
	 */
	static float EaseOutExpo(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutExpo  
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutExpo(const float Input);

	/**
	 * @brief https://easings.net/#easeInCirc  
	 * @param Input 
	 * @return 
	 */
	
	static float EaseInCirc(const float Input);
	/**
	 * @brief https://easings.net/#easeOutCirc   
	 * @param Input 
	 * @return 
	 */
	
	static float EaseOutCirc(const float Input);
	/**
	 * @brief https://easings.net/#easeInOutCirc  
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutCirc(const float Input);

	/**
	 * @brief https://easings.net/#easeInBack  
	 * @param Input 
	 * @return 
	 */
	static float EaseInBack(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutBack   
	 * @param Input 
	 * @return 
	 */
	static float EaseOutBack(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutBack  
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutBack(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInElastic  
	 * @param Input 
	 * @return 
	 */
	static float EaseInElastic(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutElastic 
	 * @param Input 
	 * @return 
	 */
	static float EaseOutElastic(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutElastic  
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutElastic(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInBounce   
	 * @param Input 
	 * @return 
	 */
	static float EaseInBounce(const float Input);
	/**
	 * @brief https://easings.net/#easeOutBounce    
	 * @param Input 
	 * @return 
	 */
	static float EaseOutBounce(const float Input);
	/**
	 * @brief https://easings.net/#easeInOutBounce    
	 * @param Input 
	 * @return 
	 */
	static float EaseInOutBounce(const float Input);

};
