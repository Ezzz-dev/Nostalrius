function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() then 
		doRelocate(item:getPosition(),{x = 32839, y = 32532, z = 09})
		item:getPosition():sendMagicEffect(21)
		Game.sendMagicEffect({x = 32839, y = 32532, z = 09}, 21)
	end
end
