function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		item:transform(430, 1)
		item:decay()
		Game.transformItemOnMap({x = 32225, y = 32282, z = 09}, 429, 438)
	end
end

function onStepOut(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		item:transform(431, 1)
		item:decay()
		Game.transformItemOnMap({x = 32225, y = 32282, z = 09}, 438, 429)
	end
end
