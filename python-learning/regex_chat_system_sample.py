import re

pattern = re.compile(r'(?P<food>.*)が食べたいです')

in_chat = '{}が食べたいです'
out_chat = 'いいですね！ 私も{}食べたいです'

foods = ['カレー', 'うどん', 'ラーメン']

for food in foods:
    user_say = in_chat.format(food)
    target = pattern.search(user_say).group('food')
    bot_say = out_chat.format(target)

    print('user:{} => bot:{}'.format(user_say, bot_say))
