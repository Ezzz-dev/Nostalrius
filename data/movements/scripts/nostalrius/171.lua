function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(323) == 1 and creature:getPlayer():isPremium() and creature:getPlayer():getItemCount(5021) >= 1 then 
		doRelocate(item:getPosition(),{x = 32498, y = 31621, z = 06})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 32498, y = 31621, z = 06}, 11)
		creature:getPlayer():removeItem(5021, 1)
	end
end
