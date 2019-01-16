function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() >= 2948 and item:getId() <= 2950 or item:getId() >= 2952 and item:getId() <= 2958 or
		item:getId() >= 2963 and item:getId() <= 2964 then
		item:getPosition():sendMagicEffect(CONST_ME_SOUND_GREEN)
	elseif (item:getId() >= 2959 and item:getId() <= 2962 or item:getId() == 2965) and math.random(1, 100) <= 50 then
		item:getPosition():sendMagicEffect(CONST_ME_SOUND_GREEN)
	elseif item:getId() >= 2959 and item:getId() <= 2962 or item:getId() == 2965 then
		item:getPosition():sendMagicEffect(CONST_ME_SOUND_PURPLE)
	elseif item:getId() == 3219 then
		item:getPosition():sendMagicEffect(19)
	end
	
	return true
end
