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
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInSine(const float Input);

	/**
	 * @brief https://easings.net/#easeOutSine
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutSine(const float Input);

	/**
	 * @brief https://easings.net/#easeInOutSine
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutSine(const float Input);

	/**
	 * @brief https://easings.net/#easeInQuad
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInQuad(const float Input);

	/**
	 * @brief https://easings.net/#easeOutQuad
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutQuad(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutQuad
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutQuad(const float Input);

	/**
	 * @brief https://easings.net/#easeInCubic 
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInCubic(const float Input);

	/**
	 * @brief https://easings.net/#easeOutCubic  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutCubic(const float Input);

	/**
	 * @brief https://easings.net/#easeInOutCubic 
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutCubic(const float Input);

	/**
	 * @brief https://easings.net/#easeInQuart 
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInQuart(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutQuart 
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutQuart(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutQuart 
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutQuart(const float Input);

	/**
	 * @brief https://easings.net/#easeInQuint  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInQuint(const float Input);
	/**
	 * @brief https://easings.net/#easeOutQuint   
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutQuint(const float Input);
	/**
	 * @brief https://easings.net/#easeInOutQuint  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutQuint(const float Input);

	/**
	 * @brief https://easings.net/#easeInExpo  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInExpo(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutExpo  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutExpo(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutExpo  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutExpo(const float Input);

	/**
	 * @brief https://easings.net/#easeInCirc  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInCirc(const float Input);
	/**
	 * @brief https://easings.net/#easeOutCirc   
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutCirc(const float Input);
	/**
	 * @brief https://easings.net/#easeInOutCirc  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutCirc(const float Input);

	/**
	 * @brief https://easings.net/#easeInBack  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInBack(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutBack   
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutBack(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutBack  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutBack(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInElastic  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInElastic(const float Input);
	
	/**
	 * @brief https://easings.net/#easeOutElastic 
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutElastic(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInOutElastic  
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutElastic(const float Input);
	
	/**
	 * @brief https://easings.net/#easeInBounce   
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInBounce(const float Input);
	/**
	 * @brief https://easings.net/#easeOutBounce    
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseOutBounce(const float Input);
	/**
	 * @brief https://easings.net/#easeInOutBounce    
	 * @param Input 
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category="Easings")
	static float EaseInOutBounce(const float Input);

};
