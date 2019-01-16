function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(293) == 7 then 
		creature:getPlayer():setStorageValue(296,1)
		item:getPosition():sendMagicEffect(13)
		item:getPosition():sendMonsterSay("!-! -O- I_I (/( --I Morgathla")
	end
end
